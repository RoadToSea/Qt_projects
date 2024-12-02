#include "controlwid.h"
#include "ui_controlwid.h"

ControlWid::ControlWid(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ControlWid)
{
    ui->setupUi(this);
}

ControlWid::~ControlWid()
{
    delete ui;
}
