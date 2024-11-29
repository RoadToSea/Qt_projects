#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "wizard.h"
#include "proopenpage.h"
#include <QFileDialog>
#include <QUrl>
#include <QtMultimedia/QAudioDevice>
#include <QtMultimedia/QAudioOutput>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),musicIndex(0)
{
    ui->setupUi(this);
    UIinit();
    ui->proTree->setObjectName("proTree");
    musicPlayer = new QMediaPlayer();
    audioOutput = new QAudioOutput();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::UIinit()
{
    //创建右侧图片显示窗口
    portrayPic = new PortrayPic();
    ui->picShow->addWidget(portrayPic);

    QAction* createPro = new QAction("创建项目",ui->menu_file);
    createPro->setShortcut(QKeySequence(Qt::CTRL|Qt::Key_N));
    ui->menu_file->addAction(createPro);

    QAction* openPro = new QAction("打开项目",ui->menu_file);
    openPro->setShortcut(QKeySequence(Qt::CTRL|Qt::Key_O));
    ui->menu_file->addAction(openPro);

    QAction* choosemusic = new QAction("选择音乐",ui->menu_setting);
    choosemusic->setShortcut(QKeySequence(Qt::CTRL|Qt::Key_J));
    ui->menu_music->addAction(choosemusic);

    QAction* turnOnMusic = new QAction("播放音乐");
    ui->menu_music->addAction(turnOnMusic);

    QAction* turnOffMusic = new QAction("停止播放");
    ui->menu_music->addAction(turnOffMusic);

    //创建项目
    connect(createPro,&QAction::triggered,this,&MainWindow::slot_createPro);
    //打开项目
    connect(openPro,&QAction::triggered,this,&MainWindow::slot_openPro);

    //打开音乐窗口
    connect(choosemusic,&QAction::triggered,this,&MainWindow::slot_chooseMusic);
    //播放音乐
    connect(turnOnMusic,&QAction::triggered,this,&MainWindow::slot_turnOnMusic);
    //停止播放
    connect(turnOffMusic,&QAction::triggered,this,&MainWindow::slot_turnOffMusic);

    //连接protree和picshow,双击绘制图片
    connect(ui->treeView,&ProTree::portrayPic,portrayPic,&PortrayPic::slot_showPic);
    //绘制上一张图片
    connect(portrayPic,&PortrayPic::showPrePic,ui->treeView,&ProTree::slot_portrayPrePic);
    //绘制下一张图片
    connect(portrayPic,&PortrayPic::showNextPic,ui->treeView,&ProTree::slot_portrayNextPic);
    //打开幻灯片窗口并播放幻灯片
    connect(ui->treeView,&ProTree::showSlideDlg,this,&MainWindow::slot_showSlideDlg);

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


/*
 * 打开幻灯片窗口并播放幻灯片
*/
void MainWindow::slot_showSlideDlg(QTreeWidgetItem* first,QTreeWidgetItem* last)
{
    slideDlg = std::make_shared<SlideDlg>(first,last);
    slideDlg->setModal(true);

    slideDlg->showMaximized();
    slideDlg->play();
}

void MainWindow::slot_chooseMusic()
{
    if(!musicWid)
        musicWid = std::make_unique<MusicWid>();
    musicWid->show();
}

void MainWindow::slot_turnOnMusic()
{
    musicPlayer->setAudioOutput(audioOutput);
    musicPlayer->setSource(musicList.at(musicIndex));
    musicPlayer->play();
}

void MainWindow::slot_turnOffMusic()
{
    musicPlayer->stop();
}


