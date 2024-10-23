#ifndef INFOHELPER_H
#define INFOHELPER_H

#include <QObject>
#include "serialmanager.h"
#include <QVector>
#include <QRunnable>
#include <QRegularExpression>

typedef struct sensor
{
    double temperature;
    double humidity;
    double pressure;
    double light;
    double accX;
    double accY;
    double accZ;
}sensorInfo;


class infoHelper : public QObject, public QRunnable
{
    Q_OBJECT
signals:
    void readyRead(sensorInfo& info);
public slots:
    void slot_startParse(QString data);
public:
    sensorInfo info;
    explicit infoHelper(QObject *parent = nullptr,SerialManager* serialmanager= nullptr);
    /*解析串口接收到的数据转换成传感器结构体*/
    const sensorInfo& parseSensorInfo(QString data);
    /*发送获取传感器数据的指令*/
    void getSensorInfo(void);
    void setSerialManager(SerialManager* pserial);
    QVector<double> parseTempAndHumi(QString& data);
    double parsePressure(QString& data);
    double parseLight(QString& data);
    QVector<double> parseAccelerate(QString& data);
    void run() override ;
private:
    SerialManager* serial;


};

#endif // INFOHELPER_H
