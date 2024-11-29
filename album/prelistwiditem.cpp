#include "prelistwiditem.h"

PreListWidItem::PreListWidItem(const QPixmap &icon, const QString &text,const int& index, QListWidget *listview, int type):
    QListWidgetItem(icon,"",listview,type),m_path(text),m_index(index)
{

}

int PreListWidItem::getIndex()
{
    return m_index;
}

QString &PreListWidItem::getPath()
{
    return m_path;
}
