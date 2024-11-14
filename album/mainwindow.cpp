#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    UIinit();
    ui->proTree->setObjectName("proTree");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::UIinit()
{
    portrayPic = new PortrayPic();
    ui->picShow->addWidget(portrayPic);

    QAction* createPro = new QAction("创建项目",ui->menu_file);
    createPro->setShortcut(QKeySequence(Qt::CTRL|Qt::Key_N));
    ui->menu_file->addAction(createPro);

    QAction* openPro = new QAction("打开项目",ui->menu_file);
    openPro->setShortcut(QKeySequence(Qt::CTRL|Qt::Key_O));
    ui->menu_file->addAction(openPro);

    QAction* music = new QAction("音乐",ui->menu_setting);
    music->setShortcut(QKeySequence(Qt::CTRL|Qt::Key_J));
    ui->menu_setting->addAction(music);

    //创建项目
    connect(createPro,&QAction::triggered,this,&MainWindow::slot_createPro);
    //打开项目
    connect(openPro,&QAction::triggered,this,&MainWindow::slot_openPro);

    //连接protree和picshow,双击绘制图片
    connect(ui->treeView,&ProTree::portrayPic,portrayPic,&PortrayPic::slot_showPic);
    //绘制上一张图片
    connect(portrayPic,&PortrayPic::showPrePic,ui->treeView,&ProTree::slot_portrayPrePic);
    //绘制下一张图片
    connect(portrayPic,&PortrayPic::showNextPic,ui->treeView,&ProTree::slot_portrayNextPic);
}

void MainWindow::slot_createPro()
{
    Wizard wizard(this);
    wizard.setWindowTitle("创建项目");
    connect(&wizard,&Wizard::finishSetting,ui->treeView,&ProTree::addItem);
    wizard.show();
    wizard.exec();
    disconnect(&wizard);
}

void MainWindow::slot_openPro()
{
    proOpenPage page(this);
    //打开项目对话框发送选中的文件名字和路径给protree 添加文件树
    connect(&page ,&proOpenPage::finishOpenPro,ui->treeView,&ProTree::addItems);
    page.openPro();
    disconnect(&page);
}
