#include "datastorethread.h"
#include "config.h"


dataStoreThread::dataStoreThread(QObject *parent)
    : QThread{parent},m_storeFlag(false)
{


}




void dataStoreThread::setStoreFlag(bool bl)
{
    QMutexLocker locker(&m_mutex);
    m_storeFlag = bl;
}

void dataStoreThread::run()
{
    //如果不允许存储就等待信号
    if(!m_storeFlag)
    {
        m_condition.wait(&m_mutex);
    }
    else
    {
        SqliteOperator::getInstance()->insertDatas(m_data);
    }
}

void dataStoreThread::slot_ReceiveSensor(QMap<QString,QString>& data)
{
    QVector<QString> tmp(8,"");
    int i=0;
    for(auto iter = data.begin();iter!=data.end();iter++)
    {
        tmp[i] = iter.value();
        ++i;
    }

    //取出数据添加到缓存中
    m_data.append(tmp);

    //如果允许存储并且数量超过MIN_STORE
    if(m_storeFlag&&m_data.size()>=MIN_STORE)
    {
        m_condition.wakeOne();
    }
    //防止数据过多占用过多内存
    if(m_data.size()>=MAX_CACHE)
    {

    }
}

