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

    // 打开串口（读写模式）
    if (!m_serial->open(QIODevice::ReadWrite)) {
        qDebug() << "无法打开串口：" << serialName;
        return;  // 如果打开失败，直接返回
    }

    // 配置串口参数
    m_serial->setBaudRate(baudRate);
    m_serial->setDataBits(dataBits);
    m_serial->setParity(parity);
    m_serial->setStopBits(stopBits);
    m_serial->setFlowControl(flowControl);

}

SerialManager::~SerialManager()
{
    m_serial->close();
}

bool SerialManager::send(QString &mes)
{
    QByteArray dataToSend = mes.toUtf8();
    qint64 bytesWritten = m_serial->write(dataToSend);

    if (bytesWritten < 0) {
        qDebug() << "发送数据失败：" << m_serial->errorString();
        return false;
    }

    m_serial->flush(); // 确保所有数据都已发送
    qDebug() << "发送成功，字节数：" << bytesWritten;
    return true;
}

QString SerialManager::read()
{
    QByteArray data = m_serial->readAll();     // 从串口读取数据
    return QString::fromUtf8(data);            // 将 QByteArray 转换为 QString
}

QSerialPort *SerialManager::getInstance()
{
    return m_serial;
}

