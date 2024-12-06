#include "dataparse.h"
#include <QMap>
#include <QDebug>

dataParse::dataParse(QObject *parent)
    : QObject{parent},m_acLabel("upstairs")
{
    QMap<QString,QString> m_data={
        {"accel_x",""},
        {"accel_y",""},
        {"accel_z",""},
        {"temperature",""},
        {"humidity",""},
        {"pressure",""},
        {"light",""},
        {"action_label",""}
    };
}

void dataParse::slot_parseData(QMap<QString, QString> &map)
{
    m_receive = map;
    for(auto iter = m_receive.begin();iter!=m_receive.end();iter++)
    {
        if(iter.key()=="i2cDrv temp\n\r")
        {
            QStringList tmp = iter.value().split(",");
            m_data["temperature"] = tmp[0];
            m_data["humidity"] = tmp[1];
        }
        else if(iter.key()=="i2cDrv press\n\r")
        {
            m_data["pressure"] = iter.value();
        }
        else if(iter.key()=="i2cDrv acc\n\r")
        {
            QStringList tmp = iter.value().split(",");
            m_data["accel_x"] = tmp[0];
            m_data["accel_y"] = tmp[1];
            m_data["accel_z"] = tmp[2];
        }
        else if(iter.key()=="i2cDrv light\n\r")
        {
            m_data["light"] = iter.value();
        }
    }
    m_data["action_label"] = m_acLabel;
    emit sig_parseOver(m_data);
}

void dataParse::slot_acLabel(const QString &text)
{
    m_acLabel = text;
}
