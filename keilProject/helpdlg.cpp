#include "helpdlg.h"
#include "ui_helpdlg.h"

#include <qfile.h>

helpDlg::helpDlg(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::helpDlg)
{
    ui->setupUi(this);
}

void helpDlg::loadMarkdown(QString path)
{
    QFile file(path);
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        qDebug()<<"helpDlg:打开文件失败";
        return;
    }
    QTextStream stream(&file);
    stream.setEncoding(QStringConverter::Utf8);
    markdown = stream.readAll();

    ui->textEdit->setMarkdown(markdown);
    file.close();
}

helpDlg::~helpDlg()
{
    delete ui;
}
