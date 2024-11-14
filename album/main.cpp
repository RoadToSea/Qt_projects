#include "mainwindow.h"

#include <QApplication>
#include <QFile>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    QFile style(":/res/style/mainwindow.qss");
    if(style.open(QFile::ReadOnly))
    {
        QString styleSheet = QLatin1String(style.readAll());
        a.setStyleSheet(styleSheet);
    }
    style.close();



    w.show();
    return a.exec();
}
