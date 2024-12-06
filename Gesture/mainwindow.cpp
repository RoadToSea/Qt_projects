#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);

    serial = new SerialManager("COM7","\n\r",QSerialPort::Baud115200);
    parser = new dataParse();

    //连接串口接受和数据处理
    connect(serial,&SerialManager::sig_dataReady,parser,&dataParse::slot_parseData);
    //连接数据解析完成和显示
    connect(parser,&dataParse::sig_parseOver,ui->dataWid,&DataWid::slot_dataReceive);
    //连接数据解析和曲线绘制
    connect(parser,&dataParse::sig_parseOver,ui->graphWid,&GraphWid::slot_update);
    //采样率
    connect(serial,&SerialManager::sig_sampleReady,ui->dataWid,&DataWid::slot_sampleReceive);
    //连接数据会绘制曲线图
    connect(parser,&dataParse::sig_parseOver,ui->graphWid,&GraphWid::slot_update);

    serial->start();


    connect(ui->sensorPage_Btn,&QPushButton::clicked,this,[&](){
        this->ui->stackedWidget->setCurrentIndex(0);
    });
    connect(ui->dataPage_Btn,&QPushButton::clicked,this,[&](){
        this->ui->stackedWidget->setCurrentIndex(1);
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}
