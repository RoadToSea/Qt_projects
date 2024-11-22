#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "portraypic.h"
#include "slidedlg.h"


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
    void slot_showSlideDlg(void);

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    PortrayPic* portrayPic;
    SlideDlg* slideDlg;
    void UIinit(void);
};
#endif // MAINWINDOW_H
