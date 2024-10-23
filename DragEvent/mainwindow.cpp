#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QUrl>
#include <QFile>
#include <QTextStream>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setAcceptDrops(true);
    ui->textEdit->setAcceptDrops(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::dragEnterEvent(QDragEnterEvent *e)
{
    if(e->mimeData()->hasUrls())
    {
        e->acceptProposedAction();
    }
    else
    {
        e->ignore();
    }
}

void MainWindow::dropEvent(QDropEvent *e)
{
    QList<QUrl> urls = e->mimeData()->urls();
    QString localUrl = urls[0].toLocalFile();
    if(localUrl.isEmpty())
        return;
    QFile fileOpen(localUrl);
    if(!fileOpen.open(QIODevice::ReadOnly))
    {
        qDebug()<<"文件打开失败";
        return;
    }
    QTextStream fileStream(&fileOpen);
    ui->textEdit->setText(fileStream.readAll());
}

