#ifndef PJTREEWIDGET_H
#define PJTREEWIDGET_H

#include <QTreeWidget>
#include "pjtreewidgetitem.h"


class PjTreeWidget : public QTreeWidget
{
    Q_OBJECT
public:
    PjTreeWidget(QWidget* parent) ;
    void addRoot(QString rootName);
    void addGroup(QString groupName);
    void addChild(QString groupName,QString childName,QString childPath);
    void addChildRecursion(QString groupName,QString directory);
    void clearTree(void);
    void deleteFileHelper(QTreeWidgetItem*fileItem,DeleteType type);
    void deleteGroupHelper(QTreeWidgetItem *groupItem,DeleteType type);
    //添加文件夹到includePath
    void addInclude(QString path);
public:
    void setIsAddInc(bool flag);
    bool& getIsAddInc(void);
protected:
private:
    QString getComplName(QString path);
    QString getName(QString path);
    QTreeWidgetItem* m_root;
    QTreeWidgetItem* m_curClick;
    QMap<QString,QTreeWidgetItem*> m_groupMap;
    bool isAddInclude;
public slots:
    void buildTree(QString pjName,QMap<QString,QVector<keilFile>> data);
    void slot_itemPressed(QTreeWidgetItem *item, int column);
private slots:
    void deleteItems(void);
    void renameItem(void);
    void addFile(void);
    void addDirectory(void);
    void addGroup(void);
};

#endif // PJTREEWIDGET_H
