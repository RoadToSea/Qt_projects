#include "datastorethread.h"
#include "config.h"


dataStoreThread::dataStoreThread(QObject *parent)
    : QThread{parent},m_storeFlag(false)
{
    qDebug()<<"线程被创建";
}




void dataStoreThread::setStoreFlag(bool bl)
{
    QMutexLocker locker(&m_mutex);
    m_storeFlag = bl;
}

void dataStoreThread::run()
{
    while (true) // 循环检查条件
    {
        m_mutex.lock();
        if (!m_storeFlag)
        {
            //qDebug() << "等待数据";
            m_condition.wait(&m_mutex);
        }
        else if (!m_data.isEmpty())
        {
            auto data = m_data;
            m_data.clear();
            m_mutex.unlock();

            //qDebug() << "处理数据";
            SqliteOperator::getInstance()->insertDatas(data);
        }
        else
        {
            m_mutex.unlock();
            QThread::msleep(100); // 延迟一小段时间，避免高占用 CPU
        }
    }
}


void dataStoreThread::slot_ReceiveSensor(QMap<QString,QString>& data)
{
    QVector<QString> tmp(8,"");
    int i=0;
    //map中的数据是无序的,不能直接通过索引访问
    for(auto iter = data.begin();iter!=data.end();iter++)
    {
        if (iter.key() == "accel_x") {
            tmp[0] = iter.value();
        } else if (iter.key() == "accel_y") {
            tmp[1] = iter.value();
        } else if (iter.key() == "accel_z") {
            tmp[2] = iter.value();
        } else if (iter.key() == "temperature") {
            tmp[3] = iter.value();
        } else if (iter.key() == "humidity") {
            tmp[4] = iter.value();
        } else if (iter.key() == "pressure") {
            tmp[5] = iter.value();
        } else if (iter.key() == "light") {
            tmp[6] = iter.value();
        } else if (iter.key() == "action_label") {
            tmp[7] = iter.value();
        }
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
        m_data.clear();
    }
}

