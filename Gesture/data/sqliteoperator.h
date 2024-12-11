#ifndef SQLITEOPERATOR_H
#define SQLITEOPERATOR_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>

class SqliteOperator : public QObject
{
    Q_OBJECT
public:
    explicit SqliteOperator(QObject *parent = nullptr);
    ~SqliteOperator();
    static std::shared_ptr<SqliteOperator> getInstance();
    bool isTableExist(QString tableName);
    void createTable(QString tableName);
    //插入单行数据
    void insertData(QVector<QString>& data);
    //插入多行数据
    void insertDatas(QVector<QVector<QString>>& datas);
    //查询总数据条数
    unsigned getTotalNum(void);
    //通过id范围查询数据
    QVector<QVector<QString>> querydataById(int start,int end);
    //通过id范围查询加速度数据
    QVector<QVector<QString>> queryAccById(int start,int end);

private:
    QSqlDatabase m_database;
signals:
};

#endif // SQLITEOPERATOR_H
