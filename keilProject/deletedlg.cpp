#include "deletedlg.h"
#include "ui_deletedlg.h"

DeleteDlg::DeleteDlg(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DeleteDlg)
{
    ui->setupUi(this);
}

DeleteDlg::~DeleteDlg()
{
    delete ui;
}

int DeleteDlg::exec()
{
    QDialog::exec();
    return type;
}

void DeleteDlg::on_deleteBtn_clicked()
{
    type = deleteFile;
    accept();
}


void DeleteDlg::on_removeBtn_clicked()
{
    type = onlyRemove;
    accept();
}


void DeleteDlg::on_cancelBtn_clicked()
{
    type = Cancel;
    accept();
}

