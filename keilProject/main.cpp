#include "./mainwindow.h"


#include <QApplication>
#include <qfile.h>
#include "control.h"

void loadQss(const QString &qssFile);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    loadQss(":/rsc/style.qss");
    w.show();
    return a.exec();
}

void loadQss(const QString &qssFile)
{
    QFile file(qssFile);
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());
    qApp->setStyleSheet(styleSheet);
}
