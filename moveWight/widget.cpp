#include "widget.h"
#include "./ui_widget.h"
#include <QRect>
#include <QScreen>
#include <QRandomGenerator>
#include "Mycustomevent.h"


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    edit = new myEdit(this);
    edit->move(100,100);
    edit->installEventFilter(edit);
    this->installEventFilter(this);

    connect(ui->pushButton,&QPushButton::clicked,this,&Widget::onButtonClicked);
    // setFixedSize(200,200);
    // installEventFilter(this); // 安装事件过滤器
}

Widget::~Widget()
{
    delete ui;
}

void Widget::onButtonClicked()
{
    MycustomEvent* ev = new MycustomEvent(12);
    QCoreApplication::postEvent(this, ev);
}

bool Widget::eventFilter(QObject *obj, QEvent *ev)
{
    if(obj == this)
    {

        // if(ev->type() == QEvent::Enter)
        // {
        //     QRect screenSize =  QApplication::primaryScreen()->geometry();
        //     int localWidth = screenSize.width()-100;
        //     int localHeight = screenSize.height()-100;

        //     int x = QRandomGenerator::global()->bounded(localWidth);
        //     int y = QRandomGenerator::global()->bounded(localHeight);

        //     move(x,y);
        // }
        if(ev->type() == QEvent::KeyPress)
        {
            qDebug()<<"wight eventFilter enter";
        }

    }
    return QWidget::eventFilter(obj,ev);
}

bool Widget::event(QEvent *ev)
{
    if (ev->type() == QEvent::KeyPress)
    {
        qDebug()<<"wight event enter";
    }
    else if(ev->type()==MycustomEvent::customType)
    {
        qDebug()<<"MycustomEvent responsed";
    }
    return QWidget::event(ev);
}
