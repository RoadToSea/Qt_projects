#include "widget.h"
#include "./ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    QCursor cursor;
    cursor.setShape(Qt::CursorShape::OpenHandCursor);
    setCursor(cursor);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::mousePressEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton && event->buttons() & Qt::RightButton)
    {
        qDebug()<<"Press down";
    }
    else if(event->button()== Qt::LeftButton)
    {
        QCursor cursor;
        cursor.setShape(Qt::CursorShape::ClosedHandCursor);
        QApplication::setOverrideCursor(cursor);
        offset = event->globalPosition()-this->pos();
    }
    else if (event->button()== Qt::RightButton)
    {
        QCursor cursor;
        cursor.setShape(Qt::CursorShape::CrossCursor);
        QApplication::setOverrideCursor(cursor);
    }

}

void Widget::mouseReleaseEvent(QMouseEvent *event)
{
    QCursor cursor;
    cursor.setShape(Qt::CursorShape::OpenHandCursor);
    QApplication::setOverrideCursor(cursor);

}

void Widget::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(event->button()==Qt::RightButton)
    {
        if(windowState() == Qt::WindowFullScreen)
        {
            setWindowState(Qt::WindowState::WindowNoState);
        }
        else
        {
            setWindowState(Qt::WindowState::WindowFullScreen);
        }
    }
}

void Widget::mouseMoveEvent(QMouseEvent *event)
{
    QPointF location = event->globalPosition()-offset;
    this->move(location.toPoint());
}

void Widget::wheelEvent(QWheelEvent *event)
{
    if(event->angleDelta().y()<0)
    {
        ui->textEdit->zoomOut();
    }
    else if(event->angleDelta().y()>0)
    {
        ui->textEdit->zoomIn();

    }

}
