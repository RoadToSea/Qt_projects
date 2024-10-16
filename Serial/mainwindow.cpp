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
}

MainWindow::~MainWindow()
{
    delete ui;
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

void MainWindow::slot_updateSerialPorts()
{

}

void MainWindow::slot_showRead()
{
    QString message = serial->read();
    ui->plainTextEdit_receive->setPlainText(message);
}


void MainWindow::on_open_btn_clicked()
{
    QString text = ui->open_btn->text();
    if(text == "打开")
    {
        QString serialName = ui->comboBox_serialName->currentText();
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
        serial = new SerialManager(serialName, baud, dataBits, parity, stopBit);


        //将串口接收绑定显示槽函数
        connect(serial->getInstance(),&QSerialPort::readyRead,this,&MainWindow::slot_showRead);

        // 更新按钮文本为 "关闭"
        ui->open_btn->setText("关闭");
        ui->open_btn->setProperty("color","off");
    }
    else
    {
        if(serial!= nullptr)
            delete serial;
        ui->open_btn->setText("打开");
        ui->open_btn->setProperty("color","on");
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
        QString message = ui->plainTextEdit_send->toPlainText();
        if(!serial->send(message))
        {
            qDebug()<<"send error";
        }
    }
}


