#include "infohelper.h"
#include <QThread>

void infoHelper::slot_startParse(QString data)
{
    parseSensorInfo(data);
}

infoHelper::infoHelper(QObject *parent, SerialManager *serialmanager):QObject{parent}
{
    serial = serialmanager;
}

void infoHelper::setSerialManager(SerialManager *pserial)
{
    serial = pserial;
}

const sensorInfo &infoHelper::parseSensorInfo(QString data)
{
    QVector<double> t = parseTempAndHumi(data);
    if(!t.isEmpty())
    {
        info.temperature = t[0];
        info.humidity = t[1];
    }
    info.pressure = parsePressure(data);
    info.light = parseLight(data);
    t=parseAccelerate(data);
    if(!t.isEmpty())
    {
        info.accX = t[0];
        info.accY = t[1];
        info.accZ = t[2];
    }
    LOG("Temperature:" << info.temperature << "℃,"
             << "Humidity:" << info.humidity << "%,"
             << "Pressure:" << info.pressure << "hPa,"
             << "Light:" << info.light << "lux,"
             << "Accelerometer X:" << info.accX << "m/s²,"
             << "Accelerometer Y:" << info.accY << "m/s²,"
        << "Accelerometer Z:" << info.accZ << "m/s²");
    emit readyRead(info);
    return info;
}

void infoHelper::getSensorInfo()
{
    serial->send(QString("i2cDrv temp"));
    serial->send(QString("i2cDrv press"));
    serial->send(QString("i2cDrv light"));
    serial->send(QString("i2cDrv acc"));
}

QVector<double> infoHelper::parseTempAndHumi(QString& data)
{
    QVector<double> ret ;
    static QRegularExpression tempRegex(R"(T = (-?\d+\.\d+) ℃, H = (\d+\.\d+)%)");
    QRegularExpressionMatch tempMatch = tempRegex.match(data);
    if(tempMatch.hasMatch())
    {
        ret.append(tempMatch.captured(1).toDouble());
        ret.append(tempMatch.captured(2).toDouble());
    }
    return ret;
}

double infoHelper::parsePressure(QString& data)
{
    double pressure=0;

    // 定义正则表达式，只匹配数字部分
    static QRegularExpression pressureRegex(R"(Pressure = (-?\d+\.\d+)hPa)");
    // 查找压力
    QRegularExpressionMatch pressureMatch = pressureRegex.match(data);
    if (pressureMatch.hasMatch()) {
        pressure = pressureMatch.captured(1).toDouble(); // 转换为 float
        }
    return pressure;
}

double infoHelper::parseLight(QString& data)
{
    double light=0;

    // 定义正则表达式，只匹配数字部分
    static QRegularExpression lightRegex(R"(Light = (\d+\.\d+)lux)");

    QRegularExpressionMatch lightMatch = lightRegex.match(data);
    if (lightMatch.hasMatch()) {
        light = lightMatch.captured(1).toDouble(); // 转换为 float
    }
    return light;
}

QVector<double> infoHelper::parseAccelerate(QString& data)
{
    QVector<double> ret;

    // 定义正则表达式，只匹配数字部分
    static QRegularExpression accRegex(R"(acc\[x\] = (-?\d+\.\d+), acc\[y\] = (-?\d+\.\d+), acc\[z\] = (-?\d+\.\d+))");
    QRegularExpressionMatch accMatch = accRegex.match(data);

    if (accMatch.hasMatch()) {
        ret.append(accMatch.captured(1).toDouble()); // 提取x轴加速度值
        ret.append(accMatch.captured(2).toDouble()); // 提取y轴加速度值
        ret.append(accMatch.captured(3).toDouble()); // 提取z轴加速度值
    }
    return ret;
}

void infoHelper::run()
{

}






