#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QKeyEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
protected:
    virtual void keyPressEvent(QKeyEvent *e);
    virtual void keyReleaseEvent(QKeyEvent *e);
private:
    Ui::Widget *ui;
    bool b_upflag = false;
    bool b_downflag = false;
    bool b_leftflag = false;
    bool b_rightflag = false;
    void updateButtonPosition(); // 移动按钮的方法
};
#endif // WIDGET_H
