#include "slidedlg.h"
#include "ui_slidedlg.h"

SlideDlg::SlideDlg(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SlideDlg)
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
}

SlideDlg::~SlideDlg()
{
    delete ui;
}

void SlideDlg::play()
{

}
