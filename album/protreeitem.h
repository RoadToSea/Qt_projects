#ifndef PROTREEITEM_H
#define PROTREEITEM_H

#include <QTreeWidgetItem>

class ProTreeItem : public QTreeWidgetItem
{
public:
    ProTreeItem(QTreeWidget* view, QString name,QString path, int type);
    ProTreeItem(QTreeWidgetItem* root,QTreeWidgetItem* parent, QString name,QString path, int type);
    void setNextItem(QTreeWidgetItem* item);
    void setPreItem(QTreeWidgetItem* item);
    QTreeWidgetItem* getNextItem(void);
    QTreeWidgetItem* getPreItem(void);
    QString getPath(void);
private:
    QString _name;
    QString _path;
    QTreeWidgetItem* _root;
    QTreeWidgetItem* _preItem;
    QTreeWidgetItem* _nextItem;
};

#endif // PROTREEITEM_H
