#ifndef PROTREETHREAD_H
#define PROTREETHREAD_H

#include <QThread>
#include "protreeitem.h"
#include "protree.h"


class proTreeThread : public QThread
{
public:
    proTreeThread(QTreeWidgetItem* root,QString& src_path,QString& dst_path,int& file_count,QObject*parent = nullptr);

private:
    QTreeWidgetItem* m_root;
    QString m_srcPath;
    QString m_dstPath;
    int fileCount;
};

#endif // PROTREETHREAD_H
