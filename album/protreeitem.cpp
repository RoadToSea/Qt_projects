#include "protreeitem.h"


ProTreeItem::ProTreeItem(QTreeWidget *view, QString name, QString path, int type):QTreeWidgetItem(view,type),
    _root(this),_name(name),_path(path),_preItem(nullptr),_nextItem(nullptr)
{

}

ProTreeItem::ProTreeItem(QTreeWidgetItem *root, QTreeWidgetItem *parent, QString name, QString path, int type):QTreeWidgetItem(parent,type),
    _root(root),_name(name),_path(path),_preItem(nullptr),_nextItem(nullptr)
{

}

void ProTreeItem::setNextItem(QTreeWidgetItem *item)
{
    _nextItem = item;
}

void ProTreeItem::setPreItem(QTreeWidgetItem *item)
{
    _preItem = item;
}

QString ProTreeItem::getPath()
{
    return _path;
}
