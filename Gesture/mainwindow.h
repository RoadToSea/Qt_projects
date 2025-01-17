#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "serialmanager.h"
#include "dataparse.h"
#include "datastorethread.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
protected:
    void paintEvent(QPaintEvent *event) override;
private:
    Ui::MainWindow *ui;
    SerialManager* serial;
    dataParse* parser;
    std::shared_ptr<dataStoreThread> worker;
private slots:
    void slot_startStore();
    void slot_stopStore();

};
#endif // MAINWINDOW_H
