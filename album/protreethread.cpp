#include "protreethread.h"

#include <QDir>
#include <QFileInfoList>
#include "config.h"
#include <QFile>
#include "protreeitem.h"

void proTreeThread::slot_cancelImport()
{
    stopFlag=true;
}

//最开始根节点和父亲节点都是root,必须初始化,不然添加节点的时候会内存异常
//父亲节点是当前要添加节点的父节点,有文件夹嵌套的情况会变化
proTreeThread::proTreeThread(QTreeWidget* self,QTreeWidgetItem* root,QString src_path,QString dst_path,
                             int& file_count,QObject*parent)
    :QThread(parent),m_self(self),m_root(root),m_parent(root),m_srcPath(src_path),m_dstPath(dst_path),m_fileCount(file_count)
{

}

//选择一个文件夹导入里面的文件
/*
    设计思路:
        判断外界是否发送停止信号,再判断是否需要复制
        -1 判断是否是文件夹,如果是,就创建节点,递归复制添加
        -2 如果是图片,就复制并添加节点到文件树
*/
void proTreeThread::importToPro(QTreeWidget* self,QTreeWidgetItem *root,QTreeWidgetItem *parent,int &file_count,QString src_path, QString dst_path,QTreeWidgetItem* pre_item)
{
    bool isCopy = true;
    //如果停止信号为true
    if(stopFlag)
        return ;
    //如果源目录和目的目录一样,就不用进行复制操作
    if(src_path == dst_path)
    {
        isCopy=false;
    }
    QDir ImportDir(src_path);
    //设置文件过滤,只要文件夹和文件,不要linux下的. ..格式
    ImportDir.setFilter(QDir::Dirs|QDir::Files|QDir::NoDotAndDotDot);
    //设置找到的文件的排序方式
    ImportDir.setSorting(QDir::Name);
    QFileInfoList fileList = ImportDir.entryInfoList();

    bool isDir = false;
    //存储要添加到节点树的路径
    QString tmpPath;
    for(QFileInfo& file:fileList)
    {
        if(stopFlag)
            return;
        //如果是文件夹,需要递归添加
        if(file.isDir())
        {
            isDir = true;
            //通知窗口更新导入进度条
            ++file_count;
            emit updateProgress(file_count);

            //使用终点路径和文件夹命构造新路径
            tmpPath = QDir(dst_path).absoluteFilePath(file.fileName());
            QDir SubDir(tmpPath);
            //如果新路径不存在就创建新的
            if(!SubDir.exists())
            {
                if(!SubDir.mkpath(tmpPath))
                    qDebug()<<"创建子项目失败";
            }
        }
        //如果不是文件夹
        else
        {
            isDir = false;
            //如果停止信号为真
            if(stopFlag)
                return;
            //获取文件后缀
            QString suffix = file.completeSuffix();
            //如果文件后缀不是图片,直接跳过
            if(suffix!= "png"&&suffix!="jpeg"&&suffix!="jpg")
                continue;
            //通知窗口更新导入进度条
            ++file_count;
            emit updateProgress(file_count);
            //将图片拷贝到当前项目文件夹下
            QDir DstDir(dst_path);
            tmpPath = DstDir.absoluteFilePath(file.fileName());
            //如果不需要复制就不会运行后面的复制代码
            if(isCopy&&!QFile::copy(file.absoluteFilePath(),tmpPath))
            {
                qDebug()<<"文件复制失败";
                continue;
            }
        }

        //依照是不是目录创建显示节点
        if(isDir)
        {
            //创建文件树显示节点
            ProTreeItem* item = new ProTreeItem(root,parent,file.fileName(),file.absoluteFilePath(),TreeItemDir);
            item->setData(0,Qt::DisplayRole,file.fileName());
            item->setData(0,Qt::DecorationRole,QIcon(":/res/icon/文件夹.svg"));
            item->setData(0,Qt::ToolTipRole,tmpPath);

            //递归创建
            QString newSrcPath = file.absoluteFilePath();
            //以当前item节点为父节点创建子项
            importToPro(self,root,item,file_count,newSrcPath,tmpPath,pre_item);
        }
        else
        {
            //通过当前文件夹下的图片构造文件树显示节点
            auto* item = new ProTreeItem(root,parent,file.fileName(),tmpPath,TreeItemPic);
            item->setData(0,Qt::DisplayRole,file.fileName());
            item->setData(0,Qt::DecorationRole,QIcon(":/res/icon/图片.svg"));
            item->setData(9,Qt::ToolTipRole,tmpPath);
            //构造双向链表方便后续访问
            if(pre_item!=nullptr)
            {
                ProTreeItem* PreItem = dynamic_cast<ProTreeItem*>(pre_item);
                PreItem->setNextItem(item);
            }
            item->setPreItem(pre_item);
            pre_item = dynamic_cast<QTreeWidgetItem*>(item);
        }
    }
}

void proTreeThread::setStopFlag(bool flag)
{
    stopFlag = flag;
}

void proTreeThread::run()
{
    importToPro(m_self,m_root,m_parent,m_fileCount,m_srcPath,m_dstPath,m_root);
    if(stopFlag)
    {
        //先从文件树中移除
        int index = m_self->indexOfTopLevelItem(m_root);
        delete m_self->takeTopLevelItem(index);
        QString path = dynamic_cast<ProTreeItem*>(m_root)->getPath();
        //再删除文件夹中的内容
        QDir dir(path);
        dir.removeRecursively();
        return;
    }

    //发送创建结束信号
    emit finishImport();
}

