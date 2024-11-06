#include "protreeitem.h"


ProTreeItem::ProTreeItem(QTreeWidget *view, QString name, QString path, int type):QTreeWidgetItem(view,type),
    _root(this),_name(name),_path(path),_preItem(nullptr),_nextItem(nullptr)
{

}

ProTreeItem::ProTreeItem(QTreeWidget *parent, QTreeWidgetItem *root, QString name, QString path, int type):QTreeWidgetItem(parent,type),
    _root(root),_name(name),_path(path),_preItem(nullptr),_nextItem(nullptr)
{

}

QString ProTreeItem::getPath()
{
    return _path;
}
