#include "portraypic.h"
#include "ui_portraypic.h"
#include "config.h"

#include <QPainter>

PortrayPic::PortrayPic(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::PortrayPic)
{
    ui->setupUi(this);
    initUI();
    ui->left_btn->installEventFilter(this);
    ui->right_btn->installEventFilter(this);
    ui->label->setFixedSize(this->width() - 50,this->height() - 20);

    connect(ui->left_btn,&picButton::btnClicked,this,&PortrayPic::slot_prePic);
    connect(ui->right_btn,&picButton::btnClicked,this,&PortrayPic::slot_nextPic);

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

/*
    在label上绘制图像

    QPixmap和QPicture:
        QPixmap:进行图像的显示和快速更新。对在屏幕显示有优化
        QPicture:记录绘图操作，尤其是当你需要在不同地方重复绘图时。

    由于每次设置图片大小都会让控件大小改变,进而让窗口大小不停变化,所以在构造函数
    中设置了label为固定大小
    这里不能使用QPainter绘制,因为painterevent事件只能绘制当前对象this,不能
    绘制子控件
*/
void PortrayPic::slot_showPic(QString &picPath)
{
    m_pixmap.load(picPath);
    int height = this->height() - 20;
    int width = this->width() -20;
    m_pixmap = m_pixmap.scaled(width,height,Qt::KeepAspectRatio);

    ui->label->setPixmap(m_pixmap);
    //ui->label->setFixedSize(width,height);

}


void PortrayPic::slot_prePic()
{
    emit showPrePic();
}

void PortrayPic::slot_nextPic()
{
    emit showNextPic();
}
