#include "proopenpage.h"
#include <QFileDialog>
#include <QDir>
#include <QFileInfo>


proOpenPage::proOpenPage(QWidget *parent)
    : QWidget{parent}
{}


void proOpenPage::openPro()
{
    QString path = QFileDialog::getExistingDirectory(this,"选择项目文件夹",QDir::currentPath(),QFileDialog::ShowDirsOnly);
    if(path.isEmpty())
        return ;
    else
    {
        QFileInfo file(path);
        QString name = file.fileName();
        QString path = file.path();
        qDebug()<<name<<"\n"<<path;
        emit finishOpenPro(name,path);
    }
}
