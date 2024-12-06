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

void DataWid::setTempAndHumi(const QString &val)
{
    QStringList vals = val.split(",");
    ui->tempLabel->setText(vals[0]);
    ui->humiLabel->setText(vals[1]);
}

void DataWid::setPress(const QString &val)
{
    ui->pressLabel->setText(val);
}

void DataWid::setLight(const QString &val)
{
    ui->lightLabel->setText(val);
}

void DataWid::setAcc(const QString &val)
{
    QStringList vals = val.split(",");
    ui->XLabel->setText(vals[0]);             // X轴
    ui->YLabel->setText(vals[1]);             // Y轴
    ui->ZLabel->setText(vals[2]);             // Z轴
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


void DataWid::parseMsg(const QString &command, const QString &val)
{
    if(command == "accel_x")
    {
        ui->XLabel->setText(val);
    }
    else if(command == "accel_y")
    {
        ui->YLabel->setText(val);
    }
    else if(command == "accel_z")
    {
        ui->ZLabel->setText(val);
    }
    else if(command == "temperature")
    {
        ui->tempLabel->setText(val);
    }
    else if(command == "humidity")
    {
        ui->humiLabel->setText(val);
    }
    else if(command == "pressure")
    {
        ui->pressLabel->setText(val);
    }
    else if(command == "light")
    {
        ui->lightLabel->setText(val);
    }

}

void DataWid::slot_dataReceive(QMap<QString, QString> &data)
{
    m_data.clear();
    m_data = data;
    for(auto iter = m_data.begin();iter!=m_data.end();iter++)
    {
        parseMsg(iter.key(),iter.value());
    }
}

void DataWid::slot_sampleReceive(unsigned int &sample)
{
    ui->rateLabel->setText(QString::number(sample));
}
