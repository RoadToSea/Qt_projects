#include "sqliteoperator.h"
#include "config.h"
#include "qdebug.h"
#include <QSqlError>


SqliteOperator::SqliteOperator(QObject *parent)
    : QObject{parent}
{
    // 检查连接是否已存在
    if (QSqlDatabase::contains("Sensor_Connection"))
    {
        m_database = QSqlDatabase::database("Sensor_Connection");
        qDebug() << "数据库连接已存在，尝试打开";
    }
    else
    {
        m_database = QSqlDatabase::addDatabase("QSQLITE", "Sensor_Connection");
        m_database.setDatabaseName("../../sqlite3/Sensor.sqlite");
        qDebug() << "创建新的数据库连接";
    }

    // 确保连接有效并打开数据库
    if (!m_database.isValid())
    {
        qDebug() << "数据库连接无效";
        return;
    }

    if (!m_database.isOpen() && !m_database.open())
    {
        qDebug() << "数据库打开失败: " << m_database.lastError().text();
        return;
    }

    qDebug() << "数据库已成功打开: " << m_database.databaseName();
}


SqliteOperator::~SqliteOperator()
{
    if(m_database.isOpen())
    {
        //如果数据库处于打开状态就关闭
        m_database.close();
    }
    qDebug()<<"数据库已关闭";
}

std::shared_ptr<SqliteOperator> SqliteOperator::getInstance()
{
    static std::shared_ptr<SqliteOperator> instance = std::make_shared<SqliteOperator>();
    return instance;
}



bool SqliteOperator::isTableExist(QString tableName)
{
    if(m_database.tables().contains(tableName))
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
    if(!m_database.isOpen())
    {
        qDebug()<<"数据库未打开";
        return;
    }
    QSqlQuery sqlQuery(m_database);
    QString table = QString("CREATE TABLE %1 (\
                                    id INTEGER PRIMARY KEY AUTOINCREMENT, -- 主键\
                                    accel_x TEXT,  -- X轴重力加速度\
                                    accel_y TEXT,  -- Y轴重力加速度\
                                    accel_z TEXT,  -- Z轴重力加速度\
                                    temperature TEXT, -- 温度\
                                    humidity TEXT,    -- 湿度\
                                    pressure TEXT,    -- 大气压力\
                                    light TEXT,       -- 光照强度\
                                    action_label TEXT -- 动作标签\
                                );"
                                ).arg(tableName);
    qDebug()<<table;

    sqlQuery.prepare(table);
    if(!sqlQuery.exec())
    {
        qDebug()<<"创建表失败\n"<< "error type:"<<sqlQuery.lastError().type()<<"\nerror text:"<<sqlQuery.lastError().text();
    }
    else
    {
        qDebug()<<"创建成功";
    }

}

void SqliteOperator::insertDatas(QVector<QVector<QString> > &datas)
{
    //qDebug()<<"开始保存";
    if(!m_database.isOpen())
    {
        qDebug()<<"存入数据:数据库未打开";
        return;
    }

    //开启事务提高效率
    m_database.transaction();

    //获取数据库操作对象
    QSqlQuery query(m_database);

    //操作语句
    static const QString intend = "INSERT INTO SensorData (accel_x, accel_y, accel_z, temperature, humidity, pressure, light, action_label) "
                     "VALUES (?, ?, ?, ?, ?, ?, ?, ?)";

    query.prepare(intend);

    //填入数据
    qDebug()<<datas;
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
            m_database.rollback();
            return;
        }
    }

    //提交事务
    if (!m_database.commit())
    {
        qDebug() << "事务提交失败: " << m_database.lastError().text();
        m_database.rollback();
        return;
    }
    qDebug()<<"保存成功";

}

unsigned int SqliteOperator::getTotalNum()
{
    unsigned result =0;
    if(!m_database.isOpen())
    {
        qDebug()<<"数据库未打开";
        return result;
    }

    QSqlQuery query(m_database);
    static const QString intend("SELECT MAX(id) FROM SensorData;");

    query.prepare(intend);
    if(!query.exec())
    {
        qDebug()<<"读取总数据条数语句执行失败"<<query.lastError().text();
        return result;
    }
    while(query.next())
    {
        result = query.value(0).toInt();
    }

    return result;
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

QVector<QVector<QString> > SqliteOperator::queryAccById(int start, int end)
{
    QVector<QVector<QString>> result;
    if(!m_database.isOpen())
    {
        qDebug()<<"读取数据:数据库未打开";
        return result;
    }

    QSqlQuery query(m_database);
    static const QString intend("SELECT action_label,accel_z "
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
        row.append(query.value(0).toString());
        row.append(query.value(1).toString());
        result.append(row);
    }
    return result;
}

