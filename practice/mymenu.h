#ifndef MYMENU_H
#define MYMENU_H

#include <QMainWindow>

namespace Ui {
class MyMenu;
}

class MyMenu : public QMainWindow
{
    Q_OBJECT

public:
    explicit MyMenu(QWidget *parent = nullptr);
    ~MyMenu();

private slots:
    void on_closeTool_Btn_clicked();

    void on_showToolAction_triggered();

    void on_changeFile_triggered();

    void slot_showInfo();

private:
    Ui::MyMenu *ui;
};

#endif // MYMENU_H
