#ifndef MUSICLISTWIDITEM_H
#define MUSICLISTWIDITEM_H

#include <QListWidgetItem>
#include <QObject>

class MusicListWidItem : public QListWidgetItem
{
public:
    MusicListWidItem(const QIcon &icon, const QString &path,const QString& name,
                     QListWidgetItem*pre = nullptr,QListWidgetItem*last=nullptr,QListWidget *listview = nullptr, int type = Type);
    QString& getPath();
    QString& getName();
    void setPreItem(QListWidgetItem* pre);
    void setLastItem(QListWidgetItem*last);
    QListWidgetItem* getPreItem(void);
    QListWidgetItem* getLastItem(void);

private:
    QString m_path;
    QString m_name;
    QListWidgetItem* preItem;
    QListWidgetItem* lastItem;
};

#endif // MUSICLISTWIDITEM_H
