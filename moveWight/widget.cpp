#include "widget.h"
#include "./ui_widget.h"
#include <QRect>
#include <QScreen>
#include <QRandomGenerator>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    edit = new myEdit(this);
    edit->move(100,100);
    // setFixedSize(200,200);
    // installEventFilter(this); // 安装事件过滤器
}

Widget::~Widget()
{
    delete ui;
}

bool Widget::eventFilter(QObject *obj, QEvent *ev)
{
    if(obj == this)
    {

        if(ev->type() == QEvent::Enter)
        {
            QRect screenSize =  QApplication::primaryScreen()->geometry();
            int localWidth = screenSize.width()-100;
            int localHeight = screenSize.height()-100;

            int x = QRandomGenerator::global()->bounded(localWidth);
            int y = QRandomGenerator::global()->bounded(localHeight);

            move(x,y);
        }

    }
    return QWidget::eventFilter(obj,ev);
}
