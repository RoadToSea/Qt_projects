#include "controlwid.h"
#include "ui_controlwid.h"

ControlWid::ControlWid(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ControlWid),m_status(false)
{
    ui->setupUi(this);

    //更改动作标签
    connect(ui->label_Combox,&QComboBox::currentIndexChanged,this,&ControlWid::slot_acLabel);
    //存入数据库
    connect(ui->storeBtn,&QPushButton::clicked,this,&ControlWid::slot_storeFlag);
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
    m_status = !m_status;
    //如果是启动存入数据库
    if(m_status)
    {
        emit sig_startStore();
    }
    else
    {
        emit sig_stopStore();
    }
}
