#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(1);

    serial = new SerialManager("COM7","\n\r",QSerialPort::Baud115200);
    parser = new dataParse();


    connect(serial,&SerialManager::sig_dataReady,parser,&dataParse::slot_parseData);;
    serial->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}
