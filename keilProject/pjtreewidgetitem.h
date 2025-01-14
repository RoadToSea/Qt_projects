#ifndef PJTREEWIDGETITEM_H
#define PJTREEWIDGETITEM_H

#include <QTreeWidgetItem>
#include "config.h"

class PjTreeWidgetItem : public QTreeWidgetItem
{
public:
    PjTreeWidgetItem(QTreeWidgetItem* parent,QString itemName,QString filePath,TreeItemType type);
    QString getName(void);
    QString getPath(void);
    void setName(QString name);
    void setPath(QString path);

private:
    QString m_itemName;
    QString m_itemPath;
};

#endif // PJTREEWIDGETITEM_H
