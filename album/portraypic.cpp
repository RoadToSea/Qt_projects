#include "portraypic.h"
#include "ui_portraypic.h"
#include "config.h"


PortrayPic::PortrayPic(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::PortrayPic)
{
    ui->setupUi(this);
    initUI();
    ui->left_btn->installEventFilter(this);
    ui->right_btn->installEventFilter(this);
}

PortrayPic::~PortrayPic()
{
    delete ui;
}

bool PortrayPic::eventFilter(QObject *object, QEvent *event)
{
    if(object->inherits("picButton"))
    {
        if(event->type() == QEvent::Enter)
        {
            picButton* btn = static_cast<picButton*>(object);
            btn->setBtnVisible(true);
        }
        else if(event->type() == QEvent::Leave)
        {
            picButton* btn = static_cast<picButton*>(object);
            btn->setBtnVisible(false);
        }
    }
    return QDialog::eventFilter(object,event);
}

void PortrayPic::initUI()
{
    //配置按钮空闲,鼠标悬浮,点击图片
    QString left_normal(LEFT_NORMAL);
    QString left_hover(LEFT_HOVER);
    QString left_clicked(LEFT_CLICKED);
    QString right_normal(RIGHT_NORMAL);
    QString right_hover(RIGHT_HOVER);
    QString right_clicked(RIGHT_CLICKED);

    ui->left_btn->setIcons(left_normal,left_hover,left_clicked);
    ui->right_btn->setIcons(right_normal,right_hover,right_clicked);

    //配置按钮动画淡入淡出效果
    ui->left_btn->setAnimation(0,1000);
    ui->right_btn->setAnimation(0,1000);
    ui->left_btn->setBtnVisible(false);
    ui->right_btn->setBtnVisible(false);
}
