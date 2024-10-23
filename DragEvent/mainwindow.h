#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDropEvent>
#include <QDragEnterEvent>
#include <QMimeData>



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
    virtual  void dragEnterEvent(QDragEnterEvent *e) override;
    virtual  void dropEvent(QDropEvent *e) override;

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
