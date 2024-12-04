#include "dataparse.h"
#include <QMap>
#include <QDebug>

dataParse::dataParse(QObject *parent)
    : QObject{parent}
{

}

void dataParse::slot_parseData(QMap<QString, QString> &map)
{
    qDebug()<<map;
    m_data = map;
    for(auto iter = m_data.begin();iter!=m_data.end();iter++)
    {
    }
}
