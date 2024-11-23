#ifndef PROTREE_H
#define PROTREE_H

#include <QTreeWidget>
#include <QSet>
#include <QAction>
#include "protreethread.h"
#include <QProgressDialog>


class ProTree : public QTreeWidget
{
    Q_OBJECT
#define PROGRESS_MAX    100
private slots:
    void slotItemPressed(QTreeWidgetItem *item, int column);
    void slotImportPro(void);
    void slot_updateProgress(int pg);
    void slot_finishImport(QTreeWidgetItem* lastItem);
    void slot_cancelImport();
    void slot_closePro();
    void slot_deletePic();
    void slot_portrayPic();
    void slot_slidePic();

public slots:
    void addItem(QString name,QString path);
    void addItems(QString name,QString path);
    void slot_portrayPrePic();
    void slot_portrayNextPic();
signals:
    void cancelImport();
    void portrayPic(QString& picPath);
    void showSlideDlg(QTreeWidgetItem* first,QTreeWidgetItem* last);
public:
    ProTree(QWidget *parent = nullptr);

private:
    QSet<QString> projects;
    QTreeWidgetItem* m_clickItem;
    QTreeWidgetItem* m_lastItem;
    std::shared_ptr<proTreeThread> m_importThread;
    QProgressDialog* m_progress;
    void constructGeneric(QString& src_path,QString& dst_path);
    void addItemGeneric(QString& name, QString& path);
    void CloseProGeneric(QTreeWidgetItem* root);
private:
    /*Actions*/
    QAction* m_actionImport;
    QAction* m_actionDelete;
    QAction* m_actionClose;
    QAction* m_actionSlide;
};

#endif // PROTREE_H
