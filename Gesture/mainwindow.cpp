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
    worker = std::make_shared<dataStoreThread>();


    //连接开启关闭高速采样模式
    connect(ui->controlWid,&ControlWid::sig_fastModeOn,serial,&SerialManager::slot_fastModeOn);
    connect(ui->controlWid,&ControlWid::sig_fastModeOFF,serial,&SerialManager::slot_fastModeOFF);

    //连接接收数据和数据解析
    connect(serial,&SerialManager::sig_dataReady,parser,&dataParse::slot_parseData);
    //连接数据解析完成和显示
    connect(parser,&dataParse::sig_parseOver,ui->dataWid,&DataWid::slot_dataReceive);
    //采样率
    connect(serial,&SerialManager::sig_sampleReady,ui->dataWid,&DataWid::slot_sampleReceive);
    //连接数据会绘制曲线图
    connect(parser,&dataParse::sig_parseOver,ui->graphWid,&GraphWid::slot_update);
    //动作标签改变通知数据解析部分
    connect(ui->controlWid,&ControlWid::sig_acLabelChange,parser,&dataParse::slot_acLabel);
    //连接数据解析和存储线程缓存
    connect(parser,&dataParse::sig_parseOver,worker.get(),&dataStoreThread::slot_ReceiveSensor);
    //是否存入数据库
    connect(ui->controlWid,&ControlWid::sig_startStore,this,&MainWindow::slot_startStore);
    connect(ui->controlWid,&ControlWid::sig_stopStore,this,&MainWindow::slot_stopStore);
    //读取数据


    //页面跳转按钮
    connect(ui->sensorPage_Btn,&QPushButton::clicked,this,[&](){
        this->ui->stackedWidget->setCurrentIndex(0);
    });
    connect(ui->dataPage_Btn,&QPushButton::clicked,this,[&](){
        this->ui->stackedWidget->setCurrentIndex(1);
    });

    serial->start();
    SqliteOperator::getInstance()->createTable("SensorData");

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void MainWindow::slot_startStore()
{
    //如果还没被创建
    if(!worker)
    {
        worker = std::make_shared<dataStoreThread>();
    }
    worker->setStoreFlag(true);
    worker->start();
}

void MainWindow::slot_stopStore()
{
    if(!worker)
        return;
    worker->setStoreFlag(false);
}
