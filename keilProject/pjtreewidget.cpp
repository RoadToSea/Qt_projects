#include "pjtreewidget.h"

#include "qlineedit.h"
#include "xmlparser.h"

#include <QMenu>
#include <qfileinfo.h>
#include <QContextMenuEvent>
#include <QApplication>
#include <QMenu>
#include <qfiledialog.h>
#include <QInputDialog>
#include <QMessageBox>
#include "deletedlg.h"



PjTreeWidget::PjTreeWidget(QWidget *parent):QTreeWidget(parent),m_root(nullptr),
    isAddInclude(true)
{
    //禁止默认的双击编辑
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    //隐藏默认的表头
    setHeaderHidden(true);
    connect(this,&QTreeWidget::itemPressed,this,&PjTreeWidget::slot_itemPressed);
}

void PjTreeWidget::addRoot(QString rootName)
{
    QTreeWidgetItem* root = new PjTreeWidgetItem(nullptr,rootName,"",TreeItemType::project);
    if(!root)
        return;
    root->setData(0,Qt::DisplayRole,rootName);
    root->setData(0,Qt::ToolTipRole,rootName);

    this->addTopLevelItem(root);
    m_root = root;
}

void PjTreeWidget::addGroup(QString groupName)
{
    if(!m_root)
        return;

    QTreeWidgetItem* group = new PjTreeWidgetItem(m_root,groupName,"",TreeItemType::group);
    if(!group)
        return;
    group->setData(0,Qt::DisplayRole,groupName);
    group->setData(0,Qt::ToolTipRole,groupName);
    group->setFlags(group->flags()|Qt::ItemIsEditable);
    m_groupMap.insert(groupName,group);

    m_root->addChild(group);
}

void PjTreeWidget::addChild(QString groupName, QString childName,QString childPath)
{
    //如果没有这个group,就返回
    auto iter = m_groupMap.find(groupName);
    if(iter == m_groupMap.end())
        return;

    //转换成相对路径
    childPath = XmlParser::getInstance()->getRelativePath(childPath);
    QTreeWidgetItem* group = iter.value();
    QTreeWidgetItem* child = new PjTreeWidgetItem(group,childName,childPath,TreeItemType::file);
    if(!child)
        return;
    child->setData(0,Qt::DisplayRole,childName);
    child->setData(0,Qt::ToolTipRole,childPath);
    child->setFlags(child->flags()|Qt::ItemIsEditable);
    group->addChild(child);
}

void PjTreeWidget::addChildRecursion(QString groupName, QString directory)
{
    QDir dir(directory);
    if(!dir.exists())
        return;
    //只有文件夹才会递归
    addInclude(dir.absolutePath());
    QFileInfoList files = dir.entryInfoList(QDir::NoDotAndDotDot | QDir::AllEntries);
    for(const QFileInfo& file:files)
    {
        if(file.isDir())
        {
            addChildRecursion(groupName,file.absoluteFilePath());
        }
        else
        {
            addChild(groupName,file.fileName(),file.absoluteFilePath());
        }
    }
}

void PjTreeWidget::clearTree()
{
    //只有文件树不为空才清空
    clear();
}

void PjTreeWidget::deleteFileHelper(QTreeWidgetItem *fileItem,DeleteType type)
{
    if(fileItem==nullptr)
        return;

    PjTreeWidgetItem* item = static_cast<PjTreeWidgetItem*>(fileItem);
    //删除本地文件
    if(type==deleteFile)
    {
        QDir dir(XmlParser::getInstance()->getPjName());
        QString filePath = dir.absoluteFilePath(item->getPath());
        QFile file(filePath);
        file.remove();
    }

    XmlParser::getInstance()->fileDelete(item->getName());

    delete fileItem;
}

void PjTreeWidget::deleteGroupHelper(QTreeWidgetItem *groupItem,DeleteType type)
{
    if(groupItem==nullptr)
        return;

    PjTreeWidgetItem* item = static_cast<PjTreeWidgetItem*>(groupItem);
    if(type==deleteFile)
    {
        QStringList pathList = XmlParser::getInstance()->getGpFilePath(item->getName());
        if(pathList.isEmpty())
            return;
        for(const QString& path:pathList)
        {
            //如果文件存在才删除
            QFile fileIndex(path);
            if(fileIndex.exists())
                fileIndex.remove();
        }
    }
    XmlParser::getInstance()->groupDelete(item->getName());
    delete groupItem;
}

void PjTreeWidget::addInclude(QString path)
{
    //优化方向: 改成添加文件夹时发送信号,将添加includePath提出TreeWidget解耦
    if(isAddInclude)
    {
        XmlParser::getInstance()->addInclude(path);
    }
}

void PjTreeWidget::setIsAddInc(bool flag)
{
    isAddInclude = flag;
}

bool &PjTreeWidget::getIsAddInc()
{
    return isAddInclude;
}

QString PjTreeWidget::getComplName(QString path)
{
    QFileInfo info(path);
    if(!info.exists())
        return "";
    return info.fileName();
}

QString PjTreeWidget::getName(QString path)
{
    QFileInfo info(path);
    if(!info.exists())
        return "";
    return info.baseName();
}

void PjTreeWidget::buildTree(QString pjName,QMap<QString,QVector<keilFile>> data)
{
    clearTree();
    addRoot(pjName);
    for(auto iter = data.begin();iter!=data.end();iter++)
    {
        QString groupName = iter.key();
        addGroup(groupName);
        QVector<keilFile> files = iter.value();
        for(const keilFile& file:files)
        {
            addChild(groupName,file.fileName,file.filePath);
        }
    }
}

void PjTreeWidget::slot_itemPressed(QTreeWidgetItem *item, int column)
{
    m_curClick = item;
    //如果是右键点击就创建菜单
    if(QGuiApplication::mouseButtons()==Qt::RightButton)
    {
        QMenu* menu = new QMenu(this);

        //删除文件或者Group
        QAction* delete_action = new QAction("删除");
        menu->addAction(delete_action);
        connect(delete_action,&QAction::triggered,this,&PjTreeWidget::deleteItems);

        //重命名
        QAction* rename_action = new QAction("重命名");
        menu->addAction(rename_action);
        connect(rename_action,&QAction::triggered,this,&PjTreeWidget::renameItem);

        if(m_curClick->type()==group)
        {
            QAction* addFile_action = new QAction("添加文件");
            QAction* addDirectory_action = new QAction("添加文件夹");
            menu->addAction(addFile_action);
            menu->addAction(addDirectory_action);
            connect(addFile_action,&QAction::triggered,this,&PjTreeWidget::addFile);
            connect(addDirectory_action,&QAction::triggered,this,&PjTreeWidget::addDirectory);
        }
        else if(m_curClick->type()==project)
        {
            QAction* addGroup_action = new QAction("添加组");
            menu->addAction(addGroup_action);
            connect(addGroup_action,&QAction::triggered,this,static_cast<void(PjTreeWidget::*)()>(&PjTreeWidget::addGroup));
        }
        //在鼠标的位置创建菜单
        menu->exec(QCursor::pos());
    }
}

void PjTreeWidget::deleteItems()
{
    qDebug()<<"deleteItems";
    DeleteDlg dlg(this);
    DeleteType type = (DeleteType)dlg.exec();
    if(type==Cancel)
        return;

    QList<QTreeWidgetItem*> items = selectedItems();
    for(QTreeWidgetItem* item:items)
    {
        PjTreeWidgetItem* select = static_cast<PjTreeWidgetItem*>(item);
        if(select->type()==file)
            deleteFileHelper(select,type);
        else if(select->type()==group)
            deleteGroupHelper(select,type);
    }
}

void PjTreeWidget::renameItem()
{
    PjTreeWidgetItem* item = static_cast<PjTreeWidgetItem*>(m_curClick);
    
    editItem(item);
}

void PjTreeWidget::addFile()
{
    qDebug()<<"addFile";

    PjTreeWidgetItem*item = static_cast<PjTreeWidgetItem*>(m_curClick);

    QFileDialog* dialog = new QFileDialog(this);
    dialog->setFileMode(QFileDialog::ExistingFiles);
    dialog->setWindowTitle("选择文件");
    if(dialog->exec()==QDialog::Accepted)
    {
        QStringList files = dialog->selectedFiles();
        for(const QString& file: files)
        {
            QFileInfo info(file);
            //添加到文件树
            addChild(item->getName(),info.fileName(),info.absoluteFilePath());
            //添加到xml
            XmlParser::getInstance()->fileInsert(item->getName(),info.absoluteFilePath());
        }
    }
}

void PjTreeWidget::addDirectory()
{
    PjTreeWidgetItem*item = static_cast<PjTreeWidgetItem*>(m_curClick);

    QFileDialog* dialog = new QFileDialog(this);
    dialog->setFileMode(QFileDialog::Directory);
    dialog->setWindowTitle("选择文件夹");
    if(dialog->exec()==QDialog::Accepted)
    {
        QStringList files = dialog->selectedFiles();
        if(files.isEmpty())
            return;
        QString dirPath = files.first();
        //添加到文件树和xml中
        addChildRecursion(item->getName(),dirPath);
        XmlParser::getInstance()->dirInsert(item->getName(),dirPath);
    }

}

void PjTreeWidget::addGroup()
{
    // 弹出输入框，提示用户输入文本
    bool ok;
    // 弹出输入框
    QString text = QInputDialog::getText(nullptr, "", "请输入Group名称:", QLineEdit::Normal, "", &ok);

    // 检查用户是否点击了“确定”
    if (!ok || text.isEmpty()) {
        return;
    }
    qDebug()<<"输入是:"<<text;
    addGroup(text);
    XmlParser::getInstance()->groupInsert(text);
}






