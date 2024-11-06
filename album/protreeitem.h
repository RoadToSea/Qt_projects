#ifndef PROTREEITEM_H
#define PROTREEITEM_H

#include <QTreeWidgetItem>

class ProTreeItem : public QTreeWidgetItem
{
public:
    ProTreeItem(QTreeWidget* view, QString name,QString path, int type);
    ProTreeItem(QTreeWidget* parent,QTreeWidgetItem* root, QString name,QString path, int type);
private:
    QString _name;
    QString _path;
    QTreeWidgetItem* _root;
    QTreeWidgetItem* _preItem;
    QTreeWidgetItem* _nextItem;

};

#endif // PROTREEITEM_H
