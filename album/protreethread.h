#ifndef PROTREETHREAD_H
#define PROTREETHREAD_H

#include <QThread>
#include "protreeitem.h"
#include "protree.h"


class proTreeThread : public QThread
{

signals:
    void updateProgress(int fc);
public:
    proTreeThread(QTreeWidget* self,QTreeWidgetItem* root,QString& src_path,QString& dst_path,int& file_count,QObject*parent = nullptr);
    void importToPro(QTreeWidgetItem *root,QTreeWidgetItem *parent,int &file_count,QString &src_path, QString &dst_path,QTreeWidgetItem* pre_item);
    void setStopFlag(bool& flag);
protected:
    void run() override;
private:
    QTreeWidget* m_self;
    QTreeWidgetItem* m_root;
    QTreeWidgetItem* m_parent;
    QString m_srcPath;
    QString m_dstPath;
    int m_fileCount;
    bool stopFlag;
};

#endif // PROTREETHREAD_H
