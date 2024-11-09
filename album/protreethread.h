#ifndef PROTREETHREAD_H
#define PROTREETHREAD_H

#include <QThread>
#include <QTreeWidget>


class proTreeThread : public QThread
{
    Q_OBJECT
signals:
    void updateProgress(int fc);
    void finishImport(void);
public slots:
    void slot_cancelImport(void);

public:
    proTreeThread(QTreeWidget* self,QTreeWidgetItem* root,QString src_path,QString dst_path,int& file_count,QObject*parent = nullptr);
    void importToPro(QTreeWidget* self,QTreeWidgetItem *root,QTreeWidgetItem *parent,int &file_count,QString src_path, QString dst_path,QTreeWidgetItem* pre_item);
    void setStopFlag(bool flag);
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
