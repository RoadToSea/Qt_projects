#include "serialmanager.h"
#include <QDebug>
#include <QTimer>
#include <qthread.h>


QMap<QString,QString> commandTemplate=
    {
        {"i2cDrv temp\n\r",""},
        {"i2cDrv press\n\r",""},
        {"i2cDrv acc\n\r",""},
        {"i2cDrv light\n\r",""}
};

QMap<QString,QString> fastCommand = {
    {"i2cDrv acc\n\r",""}
};

SerialManager::SerialManager(const QString &serialName, QString lineBreak, QSerialPort::BaudRate baudRate,
                             QSerialPort::DataBits dataBits, QSerialPort::Parity parity, QSerialPort::StopBits stopBits,
                             QSerialPort::FlowControl flowControl, QObject *parent):QObject(parent),commandIndex(0)
    ,m_commands(commandTemplate),m_linesBreak(lineBreak),m_count(0),m_sample(0),fastModeFlag(false)
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
    // if (!m_serial->open(QIODevice::ReadWrite)) {
    //     qDebug()<<"无法打开串口";
    //     return;  // 如果打开失败，直接返回
    // }

    connect(m_serial,&QSerialPort::readyRead,this,&SerialManager::readData);

    //初始化采样率定时器
    m_sampleTimer = new QTimer();
    //每秒计算一次采样率
    connect(m_sampleTimer,&QTimer::timeout,this,&SerialManager::slot_sampleCal);
}

SerialManager::~SerialManager()
{
    if(m_sampleTimer->isActive())
        m_sampleTimer->stop();
}

void SerialManager::start()
{
    //如果没有打开,尝试打开
    if(!m_serial->isOpen())
    {
        // 打开串口（读写模式）
        if (!m_serial->open(QIODevice::ReadWrite)) {
            qDebug()<<"无法打开串口";
            return;  // 如果打开失败，直接返回
        }
    }
    commandIndex =0;
    sendNextCommand();
}

void SerialManager::stop()
{
    //如果串口没有打开直接返回
    if(!m_serial->isOpen())
        return;
    m_serial->close();
    //下次再从第一条指令开始
    commandIndex =0;
}

void SerialManager::registerCommand(QMap<QString, QString> &map)
{
    m_commands = map;
}

void SerialManager::slot_fastModeOn()
{

    fastModeFlag = true;
    m_commands = fastCommand;
    commandIndex = 0;
    m_count=0;
    if(m_sampleTimer->isActive())
        m_sampleTimer->stop();
    m_serial->clear();
    sendNextCommand();
}

void SerialManager::slot_fastModeOFF()
{
    fastModeFlag = false;
    m_commands = commandTemplate;
    commandIndex = 0;
    m_count=0;
    if(m_sampleTimer->isActive())
        m_sampleTimer->stop();
    QThread::msleep(150);
    m_serial->clear();
    sendNextCommand();

}

void SerialManager::readData()
{

    // 接收当前命令的答复
    //QString str1 =m_serial->readLine();
    //QString str2 = m_serial->readLine();
    QByteArray receivedData = m_serial->readAll();
    QString reply(receivedData);
    //m_serial->clear(QSerialPort::Input);

    auto iter = m_commands.begin();
    std::advance(iter,commandIndex);
    m_commands[iter.key()] = reply;

    qDebug()<<"readline2:"<<iter.key();
    qDebug()<<"readline3:"<<reply;

    commandIndex++;
    if(commandIndex>=m_commands.size())
    {
        //一套数据接收完成,发送出去
        emit sig_dataReady(m_commands);
        emit sig_sampleReady(m_sample);
        //进行下一次接收
        commandIndex=0;
        //计数器加一
        ++m_count;
    }
    sendNextCommand();
    //QTimer::singleShot(100, this, &SerialManager::sendNextCommand);
}

void SerialManager::sendNextCommand()
{
    if(commandIndex<m_commands.size())
    {
        auto iter = m_commands.begin();
        std::advance(iter,commandIndex);
        QString cmd = iter.key();
        //qDebug()<<"current cmd:"<<cmd;
        m_serial->write(cmd.toUtf8());
        //QThread::msleep(10);

        //打开采样率计时器
        if(!m_sampleTimer->isActive())
            m_sampleTimer->start(1000);
    }
    else
    {
        //下标越界出现未知错误
        qDebug() <<  "command下标越界出现未知错误!";
        m_serial->close(); // Close when done
    }
}

void SerialManager::slot_sampleCal()
{
    m_sample = m_count;
    m_count=0;
}
