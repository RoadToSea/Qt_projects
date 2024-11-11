#include "portraypic.h"
#include "ui_portraypic.h"

PortrayPic::PortrayPic(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::PortrayPic)
{
    ui->setupUi(this);
}

PortrayPic::~PortrayPic()
{
    delete ui;
}
