#include "protree.h"
#include "qheaderview.h"
#include <QDir>
#include "protreeitem.h"
#include "config.h"
#include <QGuiApplication>
#include <QMenu>
#include <QCursor>
#include <QProgressDialog>
#include <QFileDialog>
#include <QThread>


ProTree::ProTree(QWidget *parent):QTreeWidget(parent),m_clickItem(nullptr)
{
    this->header()->hide();

    m_actionImport = new QAction("导入",this);

    //绑定点击事件
    connect(this,&ProTree::itemPressed,this,&ProTree::slotItemPressed);
    //绑定导入文件
    connect(m_actionImport,&QAction::triggered,this,&ProTree::slotImportPro);

}

void ProTree::constructGeneric(QString &src_path, QString &dst_path)
{
    //创建进度对话框
    m_progress = new QProgressDialog(this) ;
    m_progress->setRange(0,PROGRESS_MAX);
    //初始化线程连接
    int FileCount =0;
    m_importThread = std::make_shared<proTreeThread>(this,m_clickItem,std::ref(src_path),std::ref(dst_path),std::ref(FileCount));
    m_importThread->setStopFlag(false);

    //连接和线程有关的槽函数
    //连接进度对话框取消操作和导入取消
    connect(m_progress,&QProgressDialog::canceled,this,&ProTree::slot_cancelImport);
    connect(this,&ProTree::cancelImport,m_importThread.get(),&proTreeThread::slot_cancelImport);
    //连接导入完成关闭进度对话框
    connect(m_importThread.get(),&proTreeThread::finishImport,this,&ProTree::slot_finishImport);
    //连接更新进度对话框进度
    connect(m_importThread.get(),&proTreeThread::updateProgress,this,&ProTree::slot_updateProgress);

    //开启线程
    m_importThread->start();
    m_progress->show();
}

void ProTree::addItemGeneric(QString& name, QString& path)
{
    QDir dir(path);
    QString filePath = dir.absoluteFilePath(name);
    //有重复的项目路径存在
    if(projects.find(filePath)!=projects.end())
    {
        qDebug()<<"项目已存在";
        return;
    }

    QDir pro(filePath);
    //如果不存在就创建
    if(!pro.exists())
    {
        //尝试创建
        if(!pro.mkpath(filePath))
        {
            qDebug()<<"创建文件夹失败";
            return;
        }
    }

    projects.insert(filePath);
    ProTreeItem* item = new ProTreeItem(this,name,filePath,TreeItemPro);
    item->setData(0,Qt::DisplayRole,name);
    item->setData(0,Qt::DecorationRole,QIcon(":/res/icon/文件夹.svg"));
    item->setData(0,Qt::ToolTipRole,path);
    this->addTopLevelItem(item);
}

void ProTree::addItem(QString name, QString path)
{
    addItemGeneric(name,path);
}

void ProTree::addItems(QString name, QString path)
{
    addItemGeneric(name,path);
    /*****重要****/
    //设置父节点,不然添加不上节点
    m_clickItem = this->topLevelItem(0);
    QString OpenPath =path+'/'+name;
    constructGeneric(OpenPath,OpenPath);
}

void ProTree::slotItemPressed(QTreeWidgetItem *item, int column)
{
    if(QGuiApplication::mouseButtons()==Qt::RightButton)
    {

        QMenu menu(this);
        //如果是根目录
        if(item->type() == TreeItemPro)
        {
            //记录点击的列表项
            m_clickItem = item;
            //弹出菜单
            menu.addAction(m_actionImport);
            menu.exec(QCursor::pos());
        }
    }
}

void ProTree::slotImportPro()
{
    qDebug()<<"import project";
    if (m_clickItem==nullptr)
    {
        qDebug()<<"m_clickItem is nullptr";
        return;
    }

    ProTreeItem* clickItem = dynamic_cast<ProTreeItem*>(m_clickItem);

    // 弹出文件对话框
    QString path = clickItem->getPath();
    QFileDialog dialog;
    dialog.setFileMode(QFileDialog::Directory);
    dialog.setDirectory(path);
    //设置详细预览文件
    dialog.setViewMode(QFileDialog::Detail);
    QStringList fileNames;
    if(dialog.exec())
    {
        fileNames = dialog.selectedFiles();
    }
    //如果没有选择文件夹
    if(fileNames.length()<=0)
        return;
    //拿到选中的文件夹作为起始路径
    QString importPath = fileNames[0];
    //将点击的item路径作为终点路径
    ProTreeItem* dst = dynamic_cast<ProTreeItem*>(m_clickItem);
    QString DstPath = dst->getPath();

    constructGeneric(importPath,DstPath);
}


//更新进度对话框进度条
void ProTree::slot_updateProgress(int pg)
{
    if(m_progress==nullptr)
    {
        qDebug()<<"进度对话框未创建";
        return;
    }
    m_progress->setValue(pg);
}

/*
    完成文件导入
        将进度条设置成满并关闭对话框
*/
void ProTree::slot_finishImport()
{
    m_progress->setValue(PROGRESS_MAX);
    m_progress->deleteLater();
}


/*
    取消文件导入
        将对话框关闭并发送停止信号让线程停止复制删除已完成部分
*/
void ProTree::slot_cancelImport()
{
    delete m_progress;
    m_progress = nullptr;
    emit cancelImport();
}

