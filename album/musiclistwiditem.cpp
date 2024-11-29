#include "musiclistwiditem.h"


MusicListWidItem::MusicListWidItem(const QIcon &icon, const QString &path,const QString& name,QListWidgetItem*pre,QListWidgetItem*last, QListWidget *listview, int type)
    :QListWidgetItem(icon,name,listview,type),m_path(path),m_name(name)
    ,preItem(pre),lastItem(last)
{

}

QString &MusicListWidItem::getPath()
{
    return m_path;
}

QString &MusicListWidItem::getName()
{
    return m_name;
}

void MusicListWidItem::setPreItem(QListWidgetItem *pre)
{
    preItem = pre;
}

void MusicListWidItem::setLastItem(QListWidgetItem *last)
{
    lastItem = last;
}

QListWidgetItem *MusicListWidItem::getPreItem()
{
    return preItem;
}

QListWidgetItem *MusicListWidItem::getLastItem()
{
    return lastItem;
}
