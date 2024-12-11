#include "switchbtn.h"

switchBtn::switchBtn(QWidget *parent):QPushButton(parent),status(false) {

    connect(this,&QPushButton::clicked,this,&switchBtn::slot_clicked);
}

switchBtn::~switchBtn()
{
    if(Icon_ON)
        delete Icon_ON;
    if(Icon_OFF)
        delete Icon_OFF;
}

void switchBtn::setSource(QString on, QString off)
{
    Icon_ON = new QIcon(on);
    Icon_OFF = new QIcon(off);

    this->setIcon(*Icon_OFF);
    this->setIconSize(QSize(32,32));
    this->setFixedSize(QSize(32,32));
}

void switchBtn::setStatus(bool flag)
{
    status = flag;
    if(status)
    {
        this->setIcon(*Icon_ON);
    }
    else
    {
        this->setIcon(*Icon_OFF);
    }
    this->setIconSize(QSize(32,32));
    this->setFixedSize(QSize(32,32));
}

void switchBtn::reverseStatus()
{
    status = !status;
    setStatus(status);
}

void switchBtn::slot_clicked()
{
    reverseStatus();
}
