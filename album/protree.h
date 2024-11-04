#ifndef PROTREE_H
#define PROTREE_H

#include <QTreeWidget>
#include <QSet>

class ProTree : public QTreeWidget
{
public:
    ProTree(QWidget *parent = nullptr);
    void addItem(QString name,QString path);
private:
    QSet<QString> projects;
};

#endif // PROTREE_H
