#ifndef DATASTORETHREAD_H
#define DATASTORETHREAD_H

#include <QThread>
#include "qmutex.h"
#include "qwaitcondition.h"
#include "sqliteoperator.h"


class dataStoreThread : public QThread
{
    Q_OBJECT
public:
    explicit dataStoreThread(QObject *parent = nullptr);
    void setStoreFlag(bool bl);
protected:
    void run() override;
private:
    bool m_storeFlag;
    QVector<QVector<QString>> m_data;
    QMutex m_mutex;
    QWaitCondition m_condition;
public slots:
    void slot_ReceiveSensor(QMap<QString,QString>& data);
};

#endif // DATASTORETHREAD_H
