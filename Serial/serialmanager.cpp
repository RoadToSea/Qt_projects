#include "serialmanager.h"
#include <QDebug>


SerialManager::SerialManager(const QString &serialName,
                             QSerialPort::BaudRate baudRate ,
                             QSerialPort::DataBits dataBits ,
                             QSerialPort::Parity parity ,
                             QSerialPort::StopBits stopBits ,
                             QSerialPort::FlowControl flowControl ,
                             QObject *parent)
    : QObject(parent)  // 初始化父类
{
    // 创建 QSerialPort 对象并设置端口名称
    m_serial = new QSerialPort(serialName, this);

    // 配置串口参数
    m_serial->setBaudRate(baudRate);
    m_serial->setDataBits(dataBits);
    m_serial->setParity(parity);
    m_serial->setStopBits(stopBits);
    m_serial->setFlowControl(flowControl);

    // 打开串口（读写模式）
    if (!m_serial->open(QIODevice::ReadWrite)) {
        LOG("无法打开串口：" << serialName);
        return;  // 如果打开失败，直接返回
    }
    else
    {
        state = true;
    }
}

SerialManager::~SerialManager()
{
    m_serial->close();
    state=false;
}

bool SerialManager::send(QString &mes)
{
    QByteArray dataToSend = mes.toUtf8();
    if(hexSend)
    {
        dataToSend=dataToSend.toHex().toUpper();
    }
    qint64 bytesWritten = m_serial->write(dataToSend);
    //等待发送完成
    m_serial->waitForBytesWritten(1000) ;

    if (bytesWritten < 0) {
        LOG( "发送数据失败：" << m_serial->errorString());
        return false;
    }
    sendCount+=dataToSend.length();
    m_serial->flush(); // 确保所有数据都已发送
        LOG("发送成功，字节数：" << bytesWritten<<"数据是:"<<dataToSend);
    return true;
}

QString SerialManager::read()
{
    QByteArray data = m_serial->readAll();     // 从串口读取数据
    receiveCount+=data.length();
    QString ret;
    if(hexReceive)
    {
        QString temp=QString::fromUtf8(QByteArray::fromHex(data));
        for(int i=0;i<temp.length();i+=2)
        {
            ret.append(temp.mid(i,2));
            ret.append(" ");
        }
    }
    else
    {
        ret=QString::fromUtf8(data);
    }

    return ret;            // 将 QByteArray 转换为 QString
}

QSerialPort *SerialManager::getInstance()
{
    return m_serial;
}

bool SerialManager::isopen()
{
    return state;
}

unsigned int SerialManager::getsendCount()
{
    return sendCount;
}

unsigned int SerialManager::getreceiveCount()
{
    return receiveCount;
}

void SerialManager::sethexSend(bool s)
{
    hexSend=s;
}

void SerialManager::sethexReceive(bool s)
{
    hexReceive =s ;
}

void SerialManager::resetCount()
{
    sendCount=0;
    receiveCount=0;
}

