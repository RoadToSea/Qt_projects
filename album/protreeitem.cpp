#include "protreeitem.h"
#include "config.h"


ProTreeItem::ProTreeItem(QTreeWidget *view, QString name, QString path, int type):QTreeWidgetItem(view,type),
    m_root(this),m_name(name),m_path(path),m_preItem(nullptr),m_nextItem(nullptr)
{

}

ProTreeItem::ProTreeItem(QTreeWidgetItem *root, QTreeWidgetItem *parent, QString name, QString path, int type):QTreeWidgetItem(parent,type),
    m_root(root),m_name(name),m_path(path),m_preItem(nullptr),m_nextItem(nullptr)
{

}

void ProTreeItem::setNextItem(QTreeWidgetItem *item)
{
    m_nextItem = item;
}

void ProTreeItem::setPreItem(QTreeWidgetItem *item)
{
    m_preItem = item;
}

QTreeWidgetItem *ProTreeItem::getNextItem()
{
    return m_nextItem;
}

QTreeWidgetItem *ProTreeItem::getPreItem()
{
    return m_preItem;
}

QString &ProTreeItem::getName()
{
    return m_name;
}

QTreeWidgetItem *ProTreeItem::getFirstChild(QTreeWidgetItem* curItem)
{
    QTreeWidgetItem* ret = nullptr;
    //如果传入的是个空指针,返回空指针
    if(!curItem)
        return nullptr;
    //如果是图片节点,说明没有不是文件或者项目节点,没有孩子节点
    if(curItem->type()==TreeItemPic)
        return nullptr;
    unsigned childCount = curItem->childCount();
    for(int i =0 ;i<childCount;i++)
    {
        if(curItem->child(i)->type()==TreeItemPic)
            return curItem->child(i);
        //否则是文件夹节点,递归查找
        ret = getFirstChild(curItem->child(i));
        //如果找到了,就跳出循环
        if(ret)
            break;
    }
    return ret;
}

QTreeWidgetItem *ProTreeItem::getLastChild(QTreeWidgetItem* curItem)
{
    QTreeWidgetItem* ret = nullptr;
    //如果传入的是个空指针,返回空指针
    if(!curItem)
        return nullptr;
    //如果是图片节点,说明没有不是文件或者项目节点,没有孩子节点
    if(curItem->type()==TreeItemPic)
        return nullptr;
    unsigned childCount = curItem->childCount();
    for(int i =childCount-1 ;i>=0;i--)
    {
        if(curItem->child(i)->type()==TreeItemPic)
            return curItem->child(i);
        //否则是文件夹节点,递归查找
        ret = getFirstChild(curItem->child(i));
        //如果找到了,就跳出循环
        if(ret)
            break;
    }
    return ret;
}

QString& ProTreeItem::getPath()
{
    return m_path;
}
