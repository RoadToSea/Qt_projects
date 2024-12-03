#ifndef SQLITEOPERATOR_H
#define SQLITEOPERATOR_H

#include <QObject>
#include <QSqlDatabase>


class SqliteOperator : public QObject
{
    Q_OBJECT
public:
    explicit SqliteOperator(QObject *parent = nullptr);
    ~SqliteOperator();
    bool isTableExist(QString tableName);
    void createTable(QString tableName);
    void insertData(QVector<double>& data);
    void insertDatas(QVector<QVector<double>>& datas);
    void querydataById(int start,int end);
private:
    QSqlDatabase m_database;
signals:
};

#endif // SQLITEOPERATOR_H
