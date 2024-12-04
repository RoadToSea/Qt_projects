#ifndef DATAPARSE_H
#define DATAPARSE_H

#include <QObject>
#include <QMap>

class dataParse : public QObject
{
    Q_OBJECT
public:
    explicit dataParse(QObject *parent = nullptr);

private:
    QMap<QString,QString> m_data;
    QRegularExpression* expression;
signals:

public slots:
    void slot_parseData(QMap<QString,QString>& map);
};

#endif // DATAPARSE_H
