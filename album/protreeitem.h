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
    QString& getName(void);
    QTreeWidgetItem* getFirstChild(QTreeWidgetItem* curItem);
    QTreeWidgetItem* getLastChild(QTreeWidgetItem* curItem);
    QString& getPath(void);
private:
    QString m_name;
    QString m_path;
    QTreeWidgetItem* m_root;
    QTreeWidgetItem* m_preItem;
    QTreeWidgetItem* m_nextItem;
};

#endif // PROTREEITEM_H
