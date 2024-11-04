#ifndef PROTREEITEM_H
#define PROTREEITEM_H

#include <QTreeWidgetItem>

class ProTreeItem : public QTreeWidgetItem
{
public:
    ProTreeItem(QTreeWidget* view, QString name,QString path, int type);
    ProTreeItem(QTreeWidget* view,QTreeWidgetItem* root, QString name,QString path, int type);
private:
    QString _name;
    QString _path;
    QTreeWidgetItem* _preItem;
    QTreeWidgetItem* _nextItem;
    QTreeWidgetItem* _root;
};

#endif // PROTREEITEM_H
