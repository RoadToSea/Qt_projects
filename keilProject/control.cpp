#include "control.h"
#include "helpdlg.h"
#include "ui_control.h"

#include <qfiledialog.h>
#include <qtimer.h>

Control::Control(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Control),keilPath(""),filePath("")
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_StyledBackground, true); // 启用 QSS

    ui->fileBtn->setIcon(QIcon(":/rsc/directory.png"));
    ui->keilBtn->setIcon(QIcon(":/rsc/directory.png"));
    ui->helpBtn->setIcon(QIcon(":/rsc/help.png"));

    helper = new helpDlg();
    helper->loadMarkdown(":/rsc/help.md");

    timer = new QTimer();
    connect(timer,&QTimer::timeout,this,&Control::clearTips);

    connect(ui->addInclude_checkBox,&QCheckBox::stateChanged,this,&Control::slot_stateChanged);

}

Control::~Control()
{
    delete ui;
}

void Control::showTips(QString msg)
{
    ui->tips->setText(msg);
    timer->start(3000);
}

void Control::clearTips()
{
    ui->tips->clear();
    timer->stop();
}

void Control::slot_stateChanged(int state)
{
    if(state==Qt::Unchecked)
        emit sign_addIncChange(false);
    else
        emit sign_addIncChange(true);
}

void Control::on_keilBtn_clicked()
{
    QFileDialog dialog;
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setDirectory(QDir::currentPath());
    if(dialog.exec()==QFileDialog::Accepted)
    {
        QStringList fileList = dialog.selectedFiles();
        keilPath = fileList.at(0);
        QFileInfo info(keilPath);
        if(info.suffix()!="uvprojx")
        {
            showTips("keil路径错误,请确保选中文件的后缀为uvprojx");
            return;
        }
        ui->keilLineEdit->setText(keilPath);
        emit sign_keilPath(keilPath);
    }
}


void Control::on_fileBtn_clicked()
{
    QFileDialog dialog;
    dialog.setFileMode(QFileDialog::Directory);
    dialog.setDirectory(QDir::currentPath());
    if(dialog.exec()==QFileDialog::Accepted)
    {
        QStringList fileList = dialog.selectedFiles();
        filePath = fileList.at(0);
        ui->fileLineEdit->setText(filePath);
    }
}

void Control::on_importBtn_clicked()
{
    // if(keilPath.isEmpty()||filePath.isEmpty())
    //     return;

    // parser = new XmlParser(keilPath);
    // if(parser->exec(keilTag,filePath))
    // {
    //     showTips("导入成功");
    // }
    // else
    // {
    //     showTips("导入失败");
    // }
    // delete parser;
    emit sign_import();
}




void Control::on_projectLineEdit_editingFinished()
{
    keilTag = ui->projectLineEdit->text();
}


void Control::on_helpBtn_clicked()
{
    helper->show();
}
