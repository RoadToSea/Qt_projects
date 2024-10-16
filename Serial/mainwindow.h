#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "serialmanager.h"
#include "customcombox.h"


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

private slots:
    void on_page1_btn_clicked();

    void on_page2_btn_clicked();

    void on_page3_btn_clicked();

    void on_open_btn_clicked();

    void on_send_btn_clicked();

    void slot_updateSerialPorts();

    void slot_showRead();

private:
    Ui::MainWindow *ui;
    SerialManager* serial;
};
#endif // MAINWINDOW_H
