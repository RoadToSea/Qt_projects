#include "mainwindow.h"

#include <QApplication>
#include <QFile>
#include "graph/graphwid.h"
#include "sensor/datawid.h"


void applyQss(const QString qssFilePath, QApplication &app) ;



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    //DataWid w;
    w.show();
    applyQss(":/res/Gesture.qss",a);
    return a.exec();
}

void applyQss(const QString qssFilePath, QApplication &app) {
    QFile file(qssFilePath);

    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        qDebug() << "无法打开QSS文件:" << file.errorString();
        return;
    }

    QString qssContent = file.readAll();  // 读取QSS文件内容
    app.setStyleSheet(qssContent);       // 应用到整个应用程序
    file.close();
}
