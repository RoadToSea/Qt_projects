#include "prosetpage.h"
#include "ui_prosetpage.h"
#include <QLineEdit>
#include <QDir>
#include <QFileDialog>


Prosetpage::Prosetpage(QWidget *parent)
    : QWizardPage(parent)
    , ui(new Ui::Prosetpage)
{
    ui->setupUi(this);

    registerField("name",ui->ProjectName);
    registerField("path",ui->ProjectPath);

    connect(ui->ProjectName,&QLineEdit::textEdited,this,&Prosetpage::completeChanged);
    connect(ui->ProjectPath,&QLineEdit::textEdited,this,&Prosetpage::completeChanged);

    QString curDir = QDir::currentPath();
    ui->ProjectPath->setText(curDir);

    ui->ProjectName->setClearButtonEnabled(true);
    ui->ProjectPath->setClearButtonEnabled(true);

}

bool Prosetpage::isComplete() const
{
    QString ProjectName = ui->ProjectName->text();
    QString ProjectPath = ui->ProjectPath->text();
    QDir ProjectDir(ProjectPath);

    //判断选择路径是否存在
    if(!ProjectDir.exists())
    {
        ui->tips->setText("目录不存在");
        return false;
    }
    QDir FileDir = QDir(ProjectDir.absoluteFilePath(ProjectName));

    //判断选择的文件夹是否已有项目
    if(FileDir.exists())
    {
        ui->tips->setText("选择的文件夹已有项目");
        return false;
    }
    ui->tips->setText("");
    return QWizardPage::isComplete();
}

void Prosetpage::getSettings(QString &name, QString &path)
{
    name = ui->ProjectName->text();
    path = ui->ProjectPath->text();
}

Prosetpage::~Prosetpage()
{
    delete ui;
}

void Prosetpage::on_Pb_Brower_clicked()
{
    QFileDialog dialog(this,"选择文件夹",QDir::currentPath());
    dialog.setFileMode(QFileDialog::Directory);
    ui->ProjectPath->setText(dialog.getExistingDirectory());
}
