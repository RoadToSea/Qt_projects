#include "widget.h"
#include "./ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setFocusPolicy(Qt::StrongFocus);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::keyPressEvent(QKeyEvent *event) {
    if (event->isAutoRepeat()) {
        // 如果是长按导致的自动重复事件
        // 可以在这里处理连续按键的行为，比如加速移动按钮
    } else {
        // 处理正常按下的事件（非重复）
        if (event->key() == Qt::Key_Up) {
            b_upflag = true;
        }
        if (event->key() == Qt::Key_Left) {
            b_leftflag = true;
        }
        if (event->key() == Qt::Key_Down) {
            b_downflag = true;
        }
        if (event->key() == Qt::Key_Right) {
            b_rightflag = true;
        }
    }

    // 更新按钮位置
    updateButtonPosition();
}

void Widget::keyReleaseEvent(QKeyEvent *event) {
    if (event->isAutoRepeat()) {
        return;  // 忽略自动重复释放事件
    }

    // 检查释放了哪些按键
    if (event->key() == Qt::Key_Up) {
        b_upflag = false;
    }
    if (event->key() == Qt::Key_Left) {
        b_leftflag = false;
    }
    if (event->key() == Qt::Key_Down) {
        b_downflag = false;
    }
    if (event->key() == Qt::Key_Right) {
        b_rightflag = false;
    }

    // 更新按钮位置
    updateButtonPosition();
}

void Widget::updateButtonPosition()
{
    // 获取当前按钮的位置
    auto curpos = ui->pushButton->pos();

    // 根据按键组合来移动按钮
    if (b_upflag && b_downflag) {
        curpos.setY(curpos.y());  // 上下同时按下，不移动Y轴
    } else if (b_upflag) {
        curpos.setY(curpos.y() - 5);  // 向上移动
    } else if (b_downflag) {
        curpos.setY(curpos.y() + 5);  // 向下移动
    }

    if (b_leftflag && b_rightflag) {
        curpos.setX(curpos.x());  // 左右同时按下，不移动X轴
    } else if (b_leftflag) {
        curpos.setX(curpos.x() - 5);  // 向左移动
    } else if (b_rightflag) {
        curpos.setX(curpos.x() + 5);  // 向右移动
    }

    // 移动按钮到新位置
    ui->pushButton->move(curpos);
}

