#include "controlwid.h"
#include "ui_controlwid.h"
#include "sqliteoperator.h"

ControlWid::ControlWid(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ControlWid),m_storeStatus(false),m_fastStatus(false)
{
    ui->setupUi(this);

    //更改动作标签
    connect(ui->label_Combox,&QComboBox::currentIndexChanged,this,&ControlWid::slot_acLabel);
    //存入数据库按钮
    connect(ui->storeBtn,&QPushButton::clicked,this,&ControlWid::slot_storeFlag);
    //开启高速模式
    connect(ui->fastBtn,&QPushButton::clicked,this,&ControlWid::slot_fastBtn);
}

ControlWid::~ControlWid()
{
    delete ui;
}

void ControlWid::slot_acLabel(int index)
{
    QString tmp;
    switch(index)
    {
        case 0:
            tmp = "upstairs";
            break;
        case 1:
            tmp = "running";
            break;
        case 2:
            tmp = "walking";
            break;
        case 3:
            tmp = "driving";
            break;
        default:
            break;
    }
    //qDebug()<<tmp;
    emit sig_acLabelChange(tmp);
}

void ControlWid::slot_storeFlag()
{
    m_storeStatus = !m_storeStatus;
    //如果是启动存入数据库
    if(m_storeStatus)
    {
        qDebug()<<"开启存入数据库";
        emit sig_startStore();
    }
    else
    {
        qDebug()<<"停止存入数据库";
        emit sig_stopStore();
    }
}

void ControlWid::slot_fastBtn()
{
    m_fastStatus = !m_fastStatus;
    if(m_fastStatus)
    {
        emit sig_fastModeOn();
    }
    else
    {
        emit sig_fastModeOFF();
    }

}

