#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "codeeditor.h"
#include "highlighter.h"

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

private:
    Ui::MainWindow *ui;
    CodeEditor* codeEdit;
    Highlighter* highlighter;
};
#endif // MAINWINDOW_H
