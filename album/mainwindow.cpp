#include "mainwindow.h"
#include "./ui_mainwindow.h"

void MainWindow::slot_createPro()
{
    Wizard wizard(this);
    auto* page1 = wizard.page(0);
    wizard.setWindowTitle("创建项目");
    connect(&wizard,&Wizard::finishSetting,ui->treeView,&ProTree::addItem);
    wizard.show();
    wizard.exec();
    disconnect(&wizard);
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    UIinit();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::UIinit()
{
    QAction* createPro = new QAction("创建项目",ui->menu_file);
    createPro->setShortcut(QKeySequence(Qt::CTRL|Qt::Key_N));
    ui->menu_file->addAction(createPro);

    QAction* openPro = new QAction("打开项目",ui->menu_file);
    openPro->setShortcut(QKeySequence(Qt::CTRL|Qt::Key_O));
    ui->menu_file->addAction(openPro);

    QAction* music = new QAction("音乐",ui->menu_setting);
    music->setShortcut(QKeySequence(Qt::CTRL|Qt::Key_J));
    ui->menu_setting->addAction(music);

    connect(createPro,&QAction::triggered,this,&MainWindow::slot_createPro);
}
