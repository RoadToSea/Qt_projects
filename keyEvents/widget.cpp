#include "widget.h"
#include "./ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::keyPressEvent(QKeyEvent *e)
{
    if(e->modifiers() == Qt::ControlModifier)
    {
        if(e->key() == Qt::Key_M&& windowState()!=Qt::WindowFullScreen)
        {
            setWindowState(Qt::WindowFullScreen);
        }
        else if(e->key() == Qt::Key_M&& windowState()==Qt::WindowFullScreen)
        {
            setWindowState(Qt::WindowNoState);
        }
    }
    if(e->key() == Qt::Key_Escape &&windowState()==Qt::WindowFullScreen)
    {
        setWindowState(Qt::WindowNoState);
    }
}

