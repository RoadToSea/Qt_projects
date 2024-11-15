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
#include "closeprodialog.h"


ProTree::ProTree(QWidget *parent):QTreeWidget(parent),m_clickItem(nullptr),m_lastItem(nullptr)
{
    this->header()->hide();

    m_actionImport = new QAction("导入",this);
    m_actionDelete = new QAction("删除",this);
    m_actionClose = new QAction("关闭项目",this);

    //绑定点击事件
    connect(this,&ProTree::itemPressed,this,&ProTree::slotItemPressed);
    //绑定导入文件
    connect(m_actionImport,&QAction::triggered,this,&ProTree::slotImportPro);
    //绑定关闭项目
    connect(m_actionClose,&QAction::triggered,this,&ProTree::slot_closePro);
    // 绑定显示图片
    connect(this,&ProTree::itemDoubleClicked,this,&ProTree::slot_portrayPic);
    //绑定删除图片节点
    connect(m_actionDelete,&QAction::triggered,this,&ProTree::slot_deletePic);

}

/*
    导入图片到项目树
*/
void ProTree::constructGeneric(QString &src_path, QString &dst_path)
{
    //创建进度对话框
    m_progress = new QProgressDialog(this) ;
    m_progress->setRange(0,PROGRESS_MAX);
    //初始化线程连接
    int FileCount =0;
    if(!m_lastItem)
        m_lastItem = m_clickItem;
    m_importThread = std::make_shared<proTreeThread>(this,m_clickItem,m_lastItem,std::ref(src_path),std::ref(dst_path),std::ref(FileCount));
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

/*
    创建一个项目树父节点
*/
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

/*
    关闭整个项目
*/
void ProTree::CloseProGeneric(QTreeWidgetItem *root)
{
    ProTreeItem* item = dynamic_cast<ProTreeItem*>(root);
    projects.remove(item->getPath());
    root->takeChildren();
    delete root;

}

/*
    添加单个父节点,不导入数据
*/
void ProTree::addItem(QString name, QString path)
{
    addItemGeneric(name,path);
}

/*
    添加一个父节点并导入数据
*/
void ProTree::addItems(QString name, QString path)
{
    addItemGeneric(name,path);
    /*****重要****/
    //设置父节点,不然添加不上节点
    m_clickItem = this->topLevelItem(0);
    QString OpenPath =path+'/'+name;
    constructGeneric(OpenPath,OpenPath);
}

/*
    右键点击事件槽函数
*/
void ProTree::slotItemPressed(QTreeWidgetItem *item, int column)
{
    m_clickItem = item;
    if(QGuiApplication::mouseButtons()==Qt::RightButton)
    {

        QMenu menu(this);
        //记录点击的列表项
        switch (item->type())
        {
            //如果是根目录
            case TreeItemPro:
                //弹出菜单
                menu.addAction(m_actionImport);
                menu.addAction(m_actionClose);
                menu.exec(QCursor::pos());
                break;

            //如果是图片
            case TreeItemPic:
                //弹出菜单
                menu.addAction(m_actionDelete);
                menu.exec(QCursor::pos());
                break;
        }
    }
}

/*
    选中菜单中导入行为的槽函数
*/
void ProTree::slotImportPro()
{
    qDebug()<<"import project";
    if (m_clickItem==nullptr)
    {
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


/*更新进度对话框进度条*/
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
void ProTree::slot_finishImport(QTreeWidgetItem* item)
{
    m_progress->setValue(PROGRESS_MAX);
    m_progress->deleteLater();
    m_lastItem = item;
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

/*
    关闭项目
        关闭文件树但不删除
*/
void ProTree::slot_closePro()
{
    CloseProDialog dialog;
    if(QDialog::Accepted==dialog.exec())
    {
        //判断是否需要删除文件
        if(dialog.isDelete())
        {
            ProTreeItem* item = dynamic_cast<ProTreeItem*>(m_clickItem);
            QString path = item->getPath();
            QDir delete_dir(path);
            delete_dir.removeRecursively();
        }
        CloseProGeneric(m_clickItem);
    }
}

/*  删除图片
        删除文件树中选中的图片,同时删除本地图片
*/
void ProTree::slot_deletePic()
{
    ProTreeItem* item = dynamic_cast<ProTreeItem*>(m_clickItem);
    //先删除本地图片
    QString path = item->getPath();
    QFile delete_file(path);
    delete_file.remove();
    //删除树中的节点,注意是双向链表
    ProTreeItem* pre = dynamic_cast<ProTreeItem*>(item->getPreItem());
    ProTreeItem* next = dynamic_cast<ProTreeItem*>(item->getNextItem());
    //更改前后指针
    if(pre)
        pre->setNextItem(next);
    if(next)
        next->setPreItem(pre);
    item->setPreItem(nullptr);
    item->setNextItem(nullptr);
    //从树中移除自己
    m_clickItem->parent()->removeChild(m_clickItem);
    delete m_clickItem;
}

/*
    绘制图片
        在右侧空间中绘制当前双击选中的图片
*/
void ProTree::slot_portrayPic()
{
    if(QGuiApplication::mouseButtons() == Qt::LeftButton)
    {
        ProTreeItem* item = static_cast<ProTreeItem*>(m_clickItem);
        if(!item)
            return;
        //是图片节点才发送绘制信号
        if(m_clickItem->type() == TreeItemPic)
        {
            emit portrayPic(item->getPath());
        }
    }

}

/*
    接收绘制上一张图片的信号
*/
void ProTree::slot_portrayPrePic()
{
    ProTreeItem* item = static_cast<ProTreeItem*>(m_clickItem);
    if(!item)
        return;
    if(!item->getPreItem())
        return;
    m_clickItem = item->getPreItem();
    emit portrayPic(static_cast<ProTreeItem*>(item->getPreItem())->getPath());
}

/*
    接收绘制下一张图片的信号
*/
void ProTree::slot_portrayNextPic()
{
    ProTreeItem* item = static_cast<ProTreeItem*>(m_clickItem);
    if(!item)
        return;
    if(!item->getNextItem())
        return;
    m_clickItem = item->getNextItem();
    emit portrayPic(static_cast<ProTreeItem*>(item->getNextItem())->getPath());
}

