#ifndef SERIALMANAGER_H
#define SERIALMANAGER_H

#include <QObject>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QMap>


#define DEBUG 1

#if DEBUG
#define LOG(message)    qDebug()<<message
#else
#define LOG(message)
#endif

class SerialManager : public QObject
{
    Q_OBJECT
public:
    explicit SerialManager(const QString &serialName,
                           QString lineBreak,
                           QSerialPort::BaudRate baudRate = QSerialPort::Baud9600,
                           QSerialPort::DataBits dataBits = QSerialPort::Data8,
                           QSerialPort::Parity parity = QSerialPort::NoParity,
                           QSerialPort::StopBits stopBits = QSerialPort::OneStop,
                           QSerialPort::FlowControl flowControl = QSerialPort::SoftwareControl,
                           QObject *parent = nullptr);
    void start(void);
    void stop(void);
    void registerCommand(QMap<QString,QString>& map);

private:
    QSerialPort* m_serial;
    QString m_linesBreak;
    QMap<QString,QString> m_commands;
    int commandIndex;

signals:
    void sig_dataReady(QMap<QString,QString>& map);

private slots:
    void readData(void);
    void sendNextCommand(void);
};

#endif // SERIALMANAGER_H
