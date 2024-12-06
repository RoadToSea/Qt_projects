#include "datastorethread.h"
#include "config.h"


dataStoreThread::dataStoreThread(QObject *parent)
    : QThread{parent},m_storeFlag(false)
{


}

void dataStoreThread::setStoreFlag(bool bl)
{
    m_storeFlag = bl;
}

void dataStoreThread::run()
{
    if(m_storeFlag)
    {

    }
}

void dataStoreThread::slot_ReceiveSensor(QVector<double> &data)
{

}
