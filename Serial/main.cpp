#include "mainwindow.h"

#include <QApplication>
#include "test.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    //SerialAssistant w;
    w.show();
    return a.exec();
}
