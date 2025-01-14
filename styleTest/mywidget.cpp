#include "mywidget.h"
#include "ui_mywidget.h"

myWidget::myWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::myWidget)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_StyledBackground);
}

myWidget::~myWidget()
{
    delete ui;
}
