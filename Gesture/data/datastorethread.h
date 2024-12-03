#ifndef DATASTORETHREAD_H
#define DATASTORETHREAD_H

#include <QThread>
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
    QVector<QVector<double>> m_data;
    std::unique_ptr<SqliteOperator> m_operator;
public slots:
    void slot_ReceiveSensor(QVector<double>& data);
};

#endif // DATASTORETHREAD_H
