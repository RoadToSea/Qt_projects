#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QComboBox>
#include <QDebug>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //串口定时发送定时器
    sendTimer = new QTimer(this);
    //定时获取传感器数据定时器
    sensorTimer = new QTimer(this);
    helper = new infoHelper(this);
    //绑定串口定时发送函数
    connect(sendTimer,&QTimer::timeout,this,&MainWindow::slot_delaySend);
    //绑定定时获取传感器数据
    connect(sensorTimer,&QTimer::timeout,helper,&infoHelper::getSensorInfo);
    //绑定下拉查看串口端口号函数
    connect(ui->comboBox_serialName,&customCombox::pullDownList,this,&MainWindow::slot_showSerialPortsDcp);
    //绑定解析函数
    connect(this,&MainWindow::parseInfo,helper,&infoHelper::parseSensorInfo);
    //绑定解析完毕,界面显示函数
    connect(helper,&infoHelper::readyRead,this,&MainWindow::updateSensor);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateCount()
{
    QString info = QString("发送: %1\t接收: %2")
                       .arg(serial->getsendCount())
                       .arg(serial->getreceiveCount());
    ui->label_count->setText(info);
}

void MainWindow::sendHandle()
{
        QString message = ui->plainTextEdit_send->toPlainText();
        if(!serial->send(message))
        {
            LOG("send error");
            updateCount();
        }
}

void MainWindow::updateSensor(sensorInfo &info)
{
    if(info.temperature!=0)
    {
        ui->label_temp->setText(QString::number(info.temperature, 'f', 1) + "   ℃");
    }
    if(info.humidity!=0)
    {
        ui->label_humidity->setText(QString::number(info.humidity,'f',1)+"   %");
    }
    if(info.pressure!=0)
    {
        ui->label_pressure->setText(QString::number(info.pressure,'f',1)+"   hPa");
    }
    if(info.light!=0)
    {
        ui->label_light->setText(QString::number(info.light,'f',1)+"   lux");
    }
    if(info.accX!=0)
    {
        ui->label_accX->setText(QString::number(info.accX,'f',1)+"   m/s2");
    }
    if(info.accY!=0)
    {
        ui->label_accY->setText(QString::number(info.accY,'f',1)+"   m/s2");
    }
    if(info.accZ!=0)
    {
        ui->label_accZ->setText(QString::number(info.accZ,'f',1)+"   m/s2");
    }
}


void MainWindow::on_page1_btn_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_page2_btn_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void MainWindow::on_page3_btn_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::slot_showSerialPortsDcp()
{

    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        // 将可用串口添加到 comboBox
        QString portInfo ;
        portInfo.append(info.portName());
        portInfo.append("\t");
        portInfo.append(info.description());
        ui->plainTextEdit_receive->appendPlainText(portInfo);
    }
}

void MainWindow::slot_showRead()
{
    if(ui->stackedWidget->currentIndex()== 0)
    {
        QString message = serial->read();
        LOG("receive Info :"<<message);
        ui->plainTextEdit_receive->appendPlainText(message);
        updateCount();
    }
    else if(ui->stackedWidget->currentIndex() == 1)
    {
        emit parseInfo(serial->read());
    }
}


void MainWindow::on_open_btn_clicked()
{
    QString text = ui->open_btn->text();
    if(text == "打开")
    {
        QString serialName = ui->comboBox_serialName->currentText();
        QString lineBreak = "";
        QSerialPort::BaudRate baud = static_cast<QSerialPort::BaudRate>(ui->comboBox_baud->currentText().toInt());
        QSerialPort::DataBits dataBits = static_cast<QSerialPort::DataBits>(ui->comboBox_dataBit->currentText().toInt());
        QSerialPort::StopBits stopBit = QSerialPort::OneStop;
        QSerialPort::Parity  parity = QSerialPort::NoParity;
        if(ui->comboBox_stopBit->currentText()=="1")
            stopBit=QSerialPort::OneStop;
        else if(ui->comboBox_stopBit->currentText()=="1.5")
            stopBit=QSerialPort::OneAndHalfStop;
        else if(ui->comboBox_stopBit->currentText()=="2")
            stopBit=QSerialPort::TwoStop;

        // 获取串口奇偶校验位
        if(ui->comboBox_checkBit->currentText() == "无"){
            parity = QSerialPort::NoParity;
        }else if(ui->comboBox_checkBit->currentText() == "奇校验"){
            parity = QSerialPort::OddParity;
        }else if(ui->comboBox_checkBit->currentText() == "偶校验"){
            parity = QSerialPort::EvenParity;
        }
        //获取换行符
        if(ui->comboBox_lineBreak->currentText() == "\r\n")
            lineBreak = "\r\n";
        else if(ui->comboBox_lineBreak->currentText() == "\r")
            lineBreak = "\r";
        else if(ui->comboBox_lineBreak->currentText() == "\n")
            lineBreak = "\n";
        else if(ui->comboBox_lineBreak->currentText() == "\n\r")
            lineBreak = "\n\r";
        else if(ui->comboBox_lineBreak->currentText() == "无")
            lineBreak = "";

        serial = new SerialManager(serialName, lineBreak, baud, dataBits, parity, stopBit);
        if(!serial->isopen())
        {
            QMessageBox::warning(this,"警告","串口开启失败");
            return;
        }

        //将串口接收绑定显示槽函数
        connect(serial,&SerialManager::readyRead,this,&MainWindow::slot_showRead);
        //将serialManager添加到infoHelper中
        helper->setSerialManager(serial);

        //清空接收窗口
        ui->plainTextEdit_receive->clear();

        // 更新按钮文本为 "关闭"
        ui->open_btn->setText("关闭");
        ui->open_btn->setProperty("color","off");

        //锁住选择框
        chooseSelect(false);
    }
    else
    {
        if(serial!= nullptr)
            delete serial;
        ui->open_btn->setText("打开");
        ui->open_btn->setProperty("color","on");
        //释放选择框
        chooseSelect(true);
    }
    ui->open_btn->style()->polish(ui->open_btn);
}


void MainWindow::on_send_btn_clicked()
{
    //如果串口处于关闭状态,弹出警告
    if(ui->open_btn->text()=="打开")
    {
        QMessageBox::warning(this,"警告","串口未开启");
    }
    else
    {
        sendHandle();
    }
}



void MainWindow::on_clearPlace_btn_clicked()
{
    ui->plainTextEdit_receive->clear();
}


void MainWindow::on_clearCount_btn_clicked()
{
    serial->resetCount();
    updateCount();
}



void MainWindow::on_checkBox_hexReceive_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked)
        serial->sethexReceive(true);
    else
        serial->sethexReceive(false);
}


void MainWindow::on_checkBox_hexSend_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked)
        serial->sethexSend(true);
    else
        serial->sethexSend(false);
}


void MainWindow::on_checkBox_time_stateChanged(int arg1)
{
    if(arg1==Qt::Checked&&ui->open_btn->text()=="关闭")
    {
        sendTimer->start(ui->lineEdit_time->text().toInt());
    }
    else
    {
        sendTimer->stop();
    }
}

void MainWindow::slot_delaySend()
{
    //如果串口处于关闭状态,弹出警告
    if(ui->open_btn->text()=="打开")
    {
        return;
    }
    else
    {
        sendHandle();
    }
}

void MainWindow::chooseSelect(bool choice)
{
    if(choice)
    {
        ui->comboBox_serialName->setEnabled(true);
        ui->comboBox_baud->setEnabled(true);
        ui->comboBox_checkBit->setEnabled(true);
        ui->comboBox_dataBit->setEnabled(true);
        ui->comboBox_stopBit->setEnabled(true);
    }
    else
    {
        ui->comboBox_serialName->setEnabled(false);
        ui->comboBox_baud->setEnabled(false);
        ui->comboBox_checkBit->setEnabled(false);
        ui->comboBox_dataBit->setEnabled(false);
        ui->comboBox_stopBit->setEnabled(false);
    }
}



void MainWindow::on_startRead_btn_clicked()
{
    sensorTimer->start(1000);
}


void MainWindow::on_stopRead_btn_clicked()
{
    sensorTimer->stop();
}

