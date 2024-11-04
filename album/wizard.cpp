#include "wizard.h"
#include "ui_wizard.h"

Wizard::Wizard(QWidget *parent)
    : QWizard(parent)
    , ui(new Ui::Wizard)
{
    ui->setupUi(this);
}

Wizard::~Wizard()
{
    delete ui;
}

void Wizard::done(int result)
{
    //如果用户选择取消,调用父类函数关闭窗口
    if(result == QDialog::Rejected)
    {
        QWizard::done(result);
        return;
    }
    //拿到项目名称和路径并发出信号
    QString name,path;
    ui->wizardPage1->getSettings(name,path);
    emit finishSetting(name,path);
    QWizard::done(result);
}
