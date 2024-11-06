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

ProTree::ProTree(QWidget *parent):QTreeWidget(parent),m_clickItem(nullptr)
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
            //记录点击的列表项
            m_clickItem = item;
        }
    }
}

void ProTree::slotImportPro()
{
    qDebug()<<"import project";
    if (m_clickItem==nullptr)
        return;
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
    QString importPath = fileNames[0];


    //开启线程导入文件
    // QProgressDialog dialog;
    // dialog.exec();
}
