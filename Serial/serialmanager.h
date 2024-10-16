#ifndef SERIALMANAGER_H
#define SERIALMANAGER_H

#include <QObject>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>


class SerialManager : public QObject
{
    Q_OBJECT
signals:
public:
    explicit SerialManager(const QString &serialName,
                                          QSerialPort::BaudRate baudRate = QSerialPort::Baud9600,
                                          QSerialPort::DataBits dataBits = QSerialPort::Data8,
                                          QSerialPort::Parity parity = QSerialPort::NoParity,
                                          QSerialPort::StopBits stopBits = QSerialPort::OneStop,
                                          QSerialPort::FlowControl flowControl = QSerialPort::HardwareControl,
                           QObject *parent = nullptr);
    ~SerialManager();
    bool send(QString &mes);
    QString read();
    QSerialPort* getInstance();
private:
    QSerialPort* m_serial;
};

#endif // SERIALMANAGER_H
