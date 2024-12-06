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
    QMap<QString,QString> m_receive;
    QMap<QString,QString> m_data;
    QString m_acLabel;
    QRegularExpression* expression;
signals:
    void sig_parseOver(QMap<QString,QString>& data);
public slots:
    void slot_parseData(QMap<QString,QString>& map);
    void slot_acLabel(const QString& text);

};

#endif // DATAPARSE_H
