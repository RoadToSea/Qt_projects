#include "regist.h"
#include "ui_regist.h"

regist::regist(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::regist)
{
    ui->setupUi(this);
}

regist::~regist()
{
    delete ui;
}

void regist::setLogin(const std::weak_ptr<Dialog> &wp)
{
    pdialog = wp;
}
