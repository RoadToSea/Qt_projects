#ifndef PRELISTWID_H
#define PRELISTWID_H

#include <QListWidget>
#include <QObject>
#include <QTreeWidget>

class PreListWidItem;
class PreListWid : public QListWidget
{
    Q_OBJECT
public:
    PreListWid(QWidget *parent);
private:
    unsigned m_count;
    QListWidgetItem* m_curItem;
    int m_lastIndex;
    QPoint m_originPos;
    QMap<QString,PreListWidItem*> m_itemMap;
    void addListItem(QString& path);
signals:
    void sig_select(QString& path);
public slots:
    void slot_update(QTreeWidgetItem* item);
    void slot_choosed(QTreeWidgetItem* item);
    void slot_itemPressed(QListWidgetItem* item);
};

#endif // PRELISTWID_H
