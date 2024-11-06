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

    //注册域,便于将用户选择的路径传输出去
    registerField("name",ui->ProjectName);
    registerField("path",ui->ProjectPath);

    //当输入框中的文件路径出现变化,调用继承的信号,间接调用isComplete()检测路径是否合法
    connect(ui->ProjectName,&QLineEdit::textEdited,this,&Prosetpage::completeChanged);
    connect(ui->ProjectPath,&QLineEdit::textEdited,this,&Prosetpage::completeChanged);

    //设置默认路径为当前运行路径
    QString curDir = QDir::currentPath();
    ui->ProjectPath->setText(curDir);

    //添加一键清除按钮
    ui->ProjectName->setClearButtonEnabled(true);
    ui->ProjectPath->setClearButtonEnabled(true);

}

//检测路径是否合法
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

//获取注册域里name和path
void Prosetpage::getSettings(QString &name, QString &path)
{
    name = field("name").toString();
    path = field("path").toString();
}

Prosetpage::~Prosetpage()
{
    delete ui;
}

//点击浏览文件按钮槽函数
void Prosetpage::on_Pb_Brower_clicked()
{
    QFileDialog dialog(this,"选择文件夹",QDir::currentPath());
    dialog.setFileMode(QFileDialog::Directory);
    ui->ProjectPath->setText(dialog.getExistingDirectory());
}
