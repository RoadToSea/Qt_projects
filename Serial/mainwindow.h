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
    void updateCount();
    void sendHandle(void);

private slots:
    void on_page1_btn_clicked();

    void on_page2_btn_clicked();

    void on_page3_btn_clicked();

    void on_open_btn_clicked();

    void on_send_btn_clicked();

    void slot_showSerialPortsDcp();

    void slot_showRead();

    void on_clearPlace_btn_clicked();

    void on_clearCount_btn_clicked();

    void on_checkBox_hexReceive_stateChanged(int arg1);

    void on_checkBox_hexSend_stateChanged(int arg1);

    void on_checkBox_time_stateChanged(int arg1);

    void slot_delaySend(void);

private:
    Ui::MainWindow *ui;
    SerialManager* serial;
    QTimer* sendTimer;
    void chooseSelect(bool choice);
};
#endif // MAINWINDOW_H
