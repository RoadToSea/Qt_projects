#ifndef SERIALMANAGER_H
#define SERIALMANAGER_H

#include <QObject>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QMap>
#include <QTimer>

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
    ~SerialManager();
    void start(void);
    void stop(void);
    void registerCommand(QMap<QString,QString>& map);

private:
    QTimer* m_sampleTimer;
    unsigned m_count;
    unsigned m_sample;
    QSerialPort* m_serial;
    QString m_linesBreak;
    QMap<QString,QString> m_commands;
    int commandIndex;
    bool fastModeFlag ;

signals:
    void sig_dataReady(QMap<QString,QString>& map);
    void sig_sampleReady(unsigned& sample);
public slots:
    void slot_fastModeOn(void);
    void slot_fastModeOFF(void);
private slots:
    void readData(void);
    void sendNextCommand(void);
    void slot_sampleCal(void);
};

#endif // SERIALMANAGER_H
