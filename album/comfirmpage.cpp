#include "comfirmpage.h"
#include "ui_comfirmpage.h"

Comfirmpage::Comfirmpage(QWidget *parent)
    : QWizardPage(parent)
    , ui(new Ui::Comfirmpage)
{
    ui->setupUi(this);
}

Comfirmpage::~Comfirmpage()
{
    delete ui;
}
