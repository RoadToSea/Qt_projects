#include "protree.h"
#include "qheaderview.h"
#include <QDir>
#include "protreeitem.h"
#include "config.h"
#include <QGuiApplication>
#include <QMenu>
#include <QCursor>
#include <QProgressDialog>

ProTree::ProTree(QWidget *parent):QTreeWidget(parent)
{
    this->header()->hide();

    _actionImport = new QAction("导入",this);

    //绑定自定义点击事件
    connect(this,&ProTree::itemPressed,this,&ProTree::slotItemPressed);
    //绑定导入文件
    connect(_actionImport,&QAction::triggered,this,&ProTree::slotImportPro);
}

void ProTree::addItem(QString name, QString path)
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

void ProTree::slotItemPressed(QTreeWidgetItem *item, int column)
{
    if(QGuiApplication::mouseButtons()==Qt::RightButton)
    {
        QMenu menu(this);
        //如果是根目录
        if(item->type() == TreeItemPro)
        {
            //弹出菜单
            menu.addAction(_actionImport);
            menu.exec(QCursor::pos());
        }
    }
}

void ProTree::slotImportPro()
{
    qDebug()<<"import project";


    QProgressDialog dialog;
    dialog.exec();
}
