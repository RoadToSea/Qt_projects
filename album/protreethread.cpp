#include "protreethread.h"

#include <QDir>
#include <QFileInfoList>
#include "config.h"
#include <QFile>

proTreeThread::proTreeThread(QTreeWidget* self,QTreeWidgetItem* root,QString& src_path,QString& dst_path,
                             int& file_count,QObject*parent)
    :QThread(parent),m_root(root),m_srcPath(src_path),m_dstPath(dst_path),fileCount(file_count)
{

}

//选择一个文件夹导入里面的文件
void proTreeThread::importToPro(QTreeWidgetItem *root,QTreeWidgetItem *parent,int &file_count,QString &src_path, QString &dst_path,QTreeWidgetItem* pre_item)
{
    //如果停止信号为false
    if(stopFlag)
        return ;
    //如果源目录和目的目录一样,就不用进行下面的步骤
    if(src_path == dst_path)
    {
        qDebug()<<"目录一致无需复制";
    }
    else
    {
        QDir ImportDir(src_path);
        //设置文件过滤,只要文件夹和文件,不要linux下的. ..格式
        ImportDir.setFilter(QDir::Dirs|QDir::Files|QDir::NoDotAndDotDot);
        //设置找到的文件的排序方式
        ImportDir.setSorting(QDir::Name);
        QFileInfoList fileList = ImportDir.entryInfoList();
        for(QFileInfo& file:fileList)
        {
            if(stopFlag)
                return;
            //如果是文件夹,需要递归添加
            if(file.isDir())
            {
                //通知窗口更新导入进度条
                ++file_count;
                emit updateProgress(file_count);

                //使用终点路径和文件夹命构造新路径
                QString SubPath = QDir(dst_path).absoluteFilePath(file.fileName());
                QDir SubDir(SubPath);
                //如果新路径不存在就创建新的
                if(!SubDir.exists())
                {
                    if(!SubDir.mkpath(SubPath))
                        qDebug()<<"创建子项目失败";
                }

                //创建文件树显示节点
                auto* item = new ProTreeItem(m_self,root,file.fileName(),file.absoluteFilePath(),TreeItemDir);
                item->setData(0,Qt::DisplayRole,file.fileName());
                item->setData(0,Qt::DecorationRole,QIcon(":/res/icon/文件夹.svg"));
                item->setData(0,Qt::ToolTipRole,SubPath);

                //递归创建
                QString newSrcPath = file.absoluteFilePath();
                //以当前item节点为父节点创建子项
                importToPro(root,item,file_count,newSrcPath,SubPath,pre_item);
            }

            //如果不是文件夹
            else
            {
                //如果停止信号为真
                if(stopFlag)
                    return;
                //获取文件后缀
                QString suffix = file.completeSuffix();
                //如果文件后缀不是图片,直接跳过
                if(suffix!= "png"||suffix!="jpeg"||suffix!="jpg")
                    continue;
                //通知窗口更新导入进度条
                ++file_count;
                emit updateProgress(file_count);
                //将图片拷贝到当前项目文件夹下
                QDir DstDir(dst_path);
                QString DstFilePath = DstDir.absoluteFilePath(file.fileName());
                if(!QFile::copy(file.absoluteFilePath(),DstFilePath))
                {
                    qDebug()<<"文件复制失败";
                    continue;
                }
                //通过当前文件夹下的图片构造文件树显示节点
                auto* item = new ProTreeItem(m_self,root,file.fileName(),DstFilePath,TreeItemPic);
                item->setData(0,Qt::DisplayRole,file.fileName());
                item->setData(0,Qt::DecorationRole,QIcon(":/res/icon/图片.svg"));
                item->setData(9,Qt::ToolTipRole,DstFilePath);
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
    root->setExpanded(true);

}

void proTreeThread::setStopFlag(bool &flag)
{
    stopFlag = flag;
}

void proTreeThread::run()
{
    importToPro(m_root,m_parent,m_fileCount,m_srcPath,m_dstPath,m_root);
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
}
