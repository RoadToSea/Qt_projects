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
    sendTimer = new QTimer(this);
    connect(sendTimer,&QTimer::timeout,this,&MainWindow::slot_delaySend);
    connect(ui->comboBox_serialName,&customCombox::pullDownList,this,&MainWindow::slot_showSerialPortsDcp);
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
    QString message = serial->read();
    LOG("receive Info :"<<message);
    ui->plainTextEdit_receive->appendPlainText(message);
    updateCount();
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
        if(!serial->isopen())
        {
            QMessageBox::warning(this,"警告","串口开启失败");
            return;
        }

        //将串口接收绑定显示槽函数
        connect(serial->getInstance(),&QSerialPort::readyRead,this,&MainWindow::slot_showRead);

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
    if(arg1==Qt::Checked)
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


