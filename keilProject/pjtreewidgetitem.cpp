#include "pjtreewidgetitem.h"


PjTreeWidgetItem::PjTreeWidgetItem(QTreeWidgetItem* parent,QString itemName, QString filePath, TreeItemType type):
    m_itemName(itemName),m_itemPath(filePath),QTreeWidgetItem(parent,type)
{

}

QString PjTreeWidgetItem::getName()
{
    return m_itemName;
}

QString PjTreeWidgetItem::getPath()
{
    return m_itemPath;
}

void PjTreeWidgetItem::setName(QString name)
{
    m_itemName = name;
}

void PjTreeWidgetItem::setPath(QString path)
{
    m_itemPath = path;
}
