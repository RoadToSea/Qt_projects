#ifndef PRELISTWIDITEM_H
#define PRELISTWIDITEM_H

#include <QListWidgetItem>
#include <QObject>

class PreListWidItem : public QListWidgetItem
{
public:
    PreListWidItem(const QPixmap &icon, const QString &text,const int& index ,QListWidget *listview=nullptr, int type=Type);
    int getIndex();
    QString& getPath();
private:
    QString m_path;
    int m_index;

};

#endif // PRELISTWIDITEM_H
