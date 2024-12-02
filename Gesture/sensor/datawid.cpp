#include "datawid.h"
#include "ui_datawid.h"

DataWid::DataWid(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::DataWid)
{
    ui->setupUi(this);
}

DataWid::~DataWid()
{
    delete ui;
}

void DataWid::setData(QString &temp, QString &humi, QString &press, QString &light, QString &X_, QString &Y_, QString &Z_)
{
    // 更新 UI 控件的文本
    ui->tempLabel->setText(temp);        // 温度
    ui->humiLabel->setText(humi);        // 湿度
    ui->pressLabel->setText(press);      // 压力
    ui->lightLabel->setText(light);      // 光强
    ui->XLabel->setText(X_);             // X轴
    ui->YLabel->setText(Y_);             // Y轴
    ui->ZLabel->setText(Z_);             // Z轴
}


void DataWid::parseMsg(QString &command, QString &val)
{
    if(command == "")
    {

    }
    else if(command == "")
    {

    }
}

void DataWid::slot_dataReceive(QMap<QString, QString> &map)
{

}
