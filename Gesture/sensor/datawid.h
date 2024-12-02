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

private:
    Ui::DataWid *ui;
    void setData(QString& temp,QString& humi,QString& press,QString& light,
                 QString& X_,QString& Y_,QString& Z_ );
    void parseMsg(QString& command,QString& val);

public slots:
    void slot_dataReceive(QMap<QString,QString>& map);
};

#endif // DATAWID_H
