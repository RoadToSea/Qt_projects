#include "dialog.h"
#include "./ui_dialog.h"
#include <QFormLayout>
#include <QLineEdit>
#include <QDebug>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

void Dialog::initSignal()
{
    pregist = std::make_shared<regist>();
    pregist->setLogin(shared_from_this());
}

void Dialog::consol()
{
    qDebug()<<"dialog class";
}

Dialog::~Dialog()
{
    delete ui;
}


void Dialog::on_registerBtn_clicked()
{
    this->close();
    pregist->show();
}


void Dialog::on_loginBtn_clicked()
{

}

