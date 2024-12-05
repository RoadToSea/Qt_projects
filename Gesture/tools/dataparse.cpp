#include "dataparse.h"
#include <QMap>
#include <QDebug>

dataParse::dataParse(QObject *parent)
    : QObject{parent}
{

}

void dataParse::slot_parseData(QMap<QString, QString> &map)
{
    //传进来就是数据不需要解析
    //qDebug()<<map;
    //m_receive = map;
    emit sig_parseOver(map);
}
