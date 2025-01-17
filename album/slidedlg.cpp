#include "slidedlg.h"
#include "prelistwid.h"
#include "ui_slidedlg.h"

SlideDlg::SlideDlg(QTreeWidgetItem* firstItem,QTreeWidgetItem* lastItem,QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SlideDlg),m_firstItem(firstItem),m_lastItem(lastItem)
{
    // 配置按钮的空闲、鼠标悬浮、点击图片路径
    QString play_normal(PLAY_NORMAL);
    QString play_hover(PLAY_HOVER);
    QString play_press(PLAY_PRESS);
    QString stop_normal(STOP_NORMAL);
    QString stop_hover(STOP_HOVER);
    QString stop_press(STOP_PRESS);

    QString close_normal(CLOSE_NORMAL);
    QString close_hover(CLOSE_HOVER);
    QString close_press(CLOSE_PRESS);

    QString left_normal(LEFT_NORMAL);
    QString left_hover(LEFT_HOVER);
    QString left_clicked(LEFT_CLICKED);

    QString right_normal(RIGHT_NORMAL);
    QString right_hover(RIGHT_HOVER);
    QString right_clicked(RIGHT_CLICKED);


    ui->setupUi(this);
    ui->playBtn->setIcons(play_normal,play_hover,play_press,stop_normal,stop_hover,stop_press);
    ui->closeBtn->setIcons(close_normal,close_hover,close_press);
    ui->prePicBtn->setIcons(left_normal,left_hover,left_clicked);
    ui->nextPicBtn->setIcons(right_normal,right_hover,right_clicked);


    //连接暂停和继续,关闭信号
    connect(ui->playBtn,&slideStateButton::sigStart,this,&SlideDlg::play);
    connect(ui->playBtn,&slideStateButton::sigStop,this,&SlideDlg::stop);
    connect(ui->closeBtn,&picButton::released,this,&SlideDlg::close);

    //连接上一张和下一张信号
    connect(ui->prePicBtn,&picButton::clicked,ui->showPicWidget,&SlideAnimationWid::slot_prePic);
    connect(ui->nextPicBtn,&picButton::clicked,ui->showPicWidget,&SlideAnimationWid::slot_nextPic);

    //连接缩略图更新信号
    connect(ui->showPicWidget,&SlideAnimationWid::picListUpdate,ui->listPicWidget,&PreListWid::slot_update);
    //连接通知缩略图选中当前图片信号
    connect(ui->showPicWidget,&SlideAnimationWid::picListChoosed,ui->listPicWidget,&PreListWid::slot_choosed);
    //连接选中缩略图图片通知动画区域更新
    connect(ui->listPicWidget,&PreListWid::sig_select,ui->showPicWidget,&SlideAnimationWid::slot_selected) ;

    //为幻灯片控件设置第一个图片节点
    /*一定要在信号连接后,不然发送更新信号的时候信号还没连接*/
    ui->showPicWidget->setPixmap(m_firstItem);

}

SlideDlg::~SlideDlg()
{
    delete ui;
}

void SlideDlg::play()
{
    ui->showPicWidget->start();
}

void SlideDlg::stop()
{
    ui->showPicWidget->stop();
}

void SlideDlg::close()
{
    ui->showPicWidget->stop();
    this->hide();
}

