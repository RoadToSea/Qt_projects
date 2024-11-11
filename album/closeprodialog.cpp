#include "closeprodialog.h"
#include "ui_closeprodialog.h"

CloseProDialog::CloseProDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CloseProDialog),m_isDelete(false)
{
    ui->setupUi(this);

}

CloseProDialog::~CloseProDialog()
{
    delete ui;
}

bool &CloseProDialog::isDelete()
{
    return m_isDelete;
}

void CloseProDialog::on_isDeleteCheckBox_stateChanged(int arg1)
{
    if(arg1 == Qt::Unchecked)
        m_isDelete = false;
    else if(arg1 == Qt::Checked)
        m_isDelete = true;
}

