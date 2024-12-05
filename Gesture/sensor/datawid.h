#ifndef DATAWID_H
#define DATAWID_H

#include <QWidget>

namespace Ui {
class DataWid;
}

class DataWid : public QWidget
{
    Q_OBJECT

public:
    explicit DataWid(QWidget *parent = nullptr);
    ~DataWid();
    void setTempAndHumi(const QString& val);
    void setPress(const QString& val);
    void setLight(const QString& val);
    void setAcc(const QString& val);

private:
    Ui::DataWid *ui;
    QMap<QString,QString> m_data;
    void setData(QString& temp,QString& humi,QString& press,QString& light,
                 QString& X_,QString& Y_,QString& Z_ );
    void parseMsg(const QString& command,const QString& val);

public slots:
    void slot_dataReceive(QMap<QString,QString>& data);
    void slot_sampleReceive(unsigned& sample);
};

#endif // DATAWID_H
