#ifndef PROTREE_H
#define PROTREE_H

#include <QTreeWidget>
#include <QSet>
#include <QAction>


class ProTree : public QTreeWidget
{
private slots:
    void slotItemPressed(QTreeWidgetItem *item, int column);
    void slotImportPro(void);
public:
    ProTree(QWidget *parent = nullptr);
    void addItem(QString name,QString path);
private:
    QSet<QString> projects;
    QAction* _actionImport;

};

#endif // PROTREE_H
