#include "sqliteoperator.h"
#include "config.h"
#include "qdebug.h"
#include <QSqlError>


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

std::shared_ptr<SqliteOperator> SqliteOperator::getInstance()
{
    static std::shared_ptr<SqliteOperator> instance = std::make_shared<SqliteOperator>();
    return instance;
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
                                accel_x TEXT,  -- X轴重力加速度\
                                accel_y TEXT,  -- Y轴重力加速度\
                                accel_z TEXT,  -- Z轴重力加速度\
                                temperature TEXT, -- 温度\
                                humidity TEXT,    -- 湿度\
                                pressure TEXT,    -- 大气压力\
                                light TEXT,       -- 光照强度\
                                action_label TEXT -- 动作标签 "
                            );
    sqlQuery.prepare(table);
    if(!sqlQuery.exec())
    {
        qDebug()<<"创建表失败";
    }

}

void SqliteOperator::insertDatas(QVector<QVector<QString> > &datas)
{
    if(!m_database.isOpen())
    {
        qDebug()<<"存入数据:数据库未打开";
        return;
    }

    //获取数据库操作对象
    QSqlQuery query(m_database);

    //操作语句
    static const QString intend = "INSERT INTO SensorData (accel_x, accel_y, accel_z, temperature, humidity, pressure, light, action_label) "
                     "VALUES (?, ?, ?, ?, ?, ?, ?, ?)";

    query.prepare(intend);

    //填入数据

    for(QVector<QString> iter:datas)
    {
        if(iter.size()!=8)
        {
            qDebug()<<"存入数据:数据数量错误";
            return;
        }
        for(int i=0;i<iter.size();i++)
        {
            query.bindValue(i,iter[i]);
        }
        //执行语句
        if(!query.exec())
        {
            qDebug()<<"存入数据语句执行失败"<<query.lastError().text();
            return;
        }
    }

}

QVector<QVector<QString>> SqliteOperator::querydataById(int start, int end)
{
    QVector<QVector<QString>> result;
    if(!m_database.isOpen())
    {
        qDebug()<<"读取数据:数据库未打开";
        return result;
    }

    QSqlQuery query(m_database);
    static const QString intend("SELECT accel_x, accel_y, accel_z, temperature, humidity, pressure, light, action_label "
                   "FROM SensorData WHERE id >= ? AND id <= ?");

    query.prepare(intend);

    query.bindValue(0,start);
    query.bindValue(1,end);

    if(!query.exec())
    {
        qDebug()<<"读出数据语句执行失败"<<query.lastError().text();
        return result;
    }

    while(query.next())
    {
        QVector<QString> row;
        row.append(query.value(0).toString()); // accel_x
        row.append(query.value(1).toString()); // accel_y
        row.append(query.value(2).toString()); // accel_z
        row.append(query.value(3).toString()); // temperature
        row.append(query.value(4).toString()); // humidity
        row.append(query.value(5).toString()); // pressure
        row.append(query.value(6).toString()); // light
        row.append(query.value(7).toString()); // action_label

        result.append(row);
    }

    return result;
}

