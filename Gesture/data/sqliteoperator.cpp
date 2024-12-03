#include "sqliteoperator.h"
#include "config.h"
#include "qdebug.h"

#include <QSqlQuery>

SqliteOperator::SqliteOperator(QObject *parent)
    : QObject{parent}
{
    if(QSqlDatabase::contains("Sensor_Connection"))
    {
        //如果已经存在
        m_database = QSqlDatabase::database("SensorDatabase");
    }
    else
    {
        //如果不存在连接
        // 建立和SQlite数据库的连接
        m_database = QSqlDatabase::addDatabase("QSQLITE");
        // 设置数据库文件的名字
        m_database.setDatabaseName("Sensor.db");
    }

    if(!m_database.isOpen())
    {
        if(!m_database.open())
        {
            qDebug()<<"数据库打开失败";
        }
    }


}

SqliteOperator::~SqliteOperator()
{
    if(m_database.isOpen())
    {
        //如果数据库处于打开状态就关闭
        m_database.close();
    }
}

bool SqliteOperator::isTableExist(QString tableName)
{
    QSqlDatabase database = QSqlDatabase::database("SensorDatabase");
    if(database.tables().contains(tableName))
    {
        //已经存在
        return true;
    }
    return false;
}

void SqliteOperator::createTable(QString tableName)
{
    if(isTableExist(tableName))
    {
        //表已经存在
        return ;
    }
    QSqlQuery sqlQuery;
    QString table = QString("CREATE TABLE SensorData (\
                                id INTEGER PRIMARY KEY AUTOINCREMENT, -- 主键\
                                accel_x REAL,  -- X轴重力加速度\
                                accel_y REAL,  -- Y轴重力加速度\
                                accel_z REAL,  -- Z轴重力加速度\
                                temperature REAL, -- 温度\
                                humidity REAL,    -- 湿度\
                                pressure REAL,    -- 大气压力\
                                light REAL,       -- 光照强度\
                                action_label INTEGER -- 动作标签 (整数枚举类型)"
                            );
    sqlQuery.prepare(table);
    if(!sqlQuery.exec())
    {
        qDebug()<<"创建表失败";
    }

}

