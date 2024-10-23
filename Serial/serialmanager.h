#ifndef SERIALMANAGER_H
#define SERIALMANAGER_H

#include <QObject>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QTimer>


#define DEBUG 0

#if DEBUG
    #define LOG(message)    qDebug()<<message
#else
    #define LOG(message)
#endif

class SerialManager : public QObject
{
    Q_OBJECT
signals:
    void readyRead();
public:
    //流控不可改成硬件流控,否则发送不成功
    explicit SerialManager(const QString &serialName,
                                          QSerialPort::BaudRate baudRate = QSerialPort::Baud9600,
                                          QSerialPort::DataBits dataBits = QSerialPort::Data8,
                                          QSerialPort::Parity parity = QSerialPort::NoParity,
                                          QSerialPort::StopBits stopBits = QSerialPort::OneStop,
                                          QSerialPort::FlowControl flowControl = QSerialPort::SoftwareControl,
                           QObject *parent = nullptr);
    ~SerialManager();
    bool send(QString mes);
    QString read();
    QSerialPort* getInstance();
    bool isopen();
    unsigned getsendCount();
    unsigned getreceiveCount();
    void sethexSend(bool s);
    void sethexReceive(bool s);
    void resetCount();
private:
    QByteArray buf;
    QSerialPort* m_serial;
    bool state=false;
    unsigned sendCount=0;
    unsigned receiveCount=0;
    bool hexSend=false;
    bool hexReceive =false;
    void readHandler();
};


#endif // SERIALMANAGER_H
