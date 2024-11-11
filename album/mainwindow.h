#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "wizard.h"
#include "proopenpage.h"
#include "portraypic.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public slots:
    void slot_createPro(void);
    void slot_openPro(void);

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    PortrayPic* portrayPic;
    void UIinit(void);
};
#endif // MAINWINDOW_H
