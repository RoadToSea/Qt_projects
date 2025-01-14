#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>
#include <QTimer>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->control,&Control::sign_keilPath,this,&MainWindow::slot_keilPath);
    connect(ui->control,&Control::sign_import,this,&MainWindow::slot_import);
    connect(ui->control,&Control::sign_addIncChange,ui->pjTree,&PjTree::slot_addInc);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slot_keilPath(QString &path)
{
    //xmlParser为空,初始化
    if(XmlParser::getInstance(path)==nullptr)
        XmlParser::getInstance(path);
    else
        XmlParser::getInstance()->loadXml(path);

    if (QObject::sender() != XmlParser::getInstance()) {
        // 只有信号没有被链接过才链接
        connect(XmlParser::getInstance(), &XmlParser::sign_keilPjChanged, ui->pjTree, &PjTree::slot_PjChanged);
    }
    connect(XmlParser::getInstance(),&XmlParser::sign_keilPjChanged,ui->pjTree,&PjTree::slot_PjChanged);

    //发送构造文件树信号
    ui->pjTree->slot_PjChanged();
}

void MainWindow::slot_import()
{
    XmlParser::getInstance()->save();
}




