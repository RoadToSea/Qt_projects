#include "picbutton.h"



picButton::picButton(QWidget *parent): QPushButton(parent)
{
    initUI();
}

void picButton::setIcons(QString &normal, QString &hover, QString &clicked)
{
    m_normal = normal;
    m_hover = hover;
    m_clicked = clicked;

    QPixmap tmp;
    tmp.load(m_normal);
    this->setIcon(tmp);
    this->resize(tmp.size());
    this->setIconSize(tmp.size());
}

/*

*/
void picButton::setOpacity(double op)
{
    Opacity = op;
}

/*
    设置动画参数
        @opacityVal: 透明度
        @duration_msec:动画持续时间(ms)
*/
void picButton::setAnimation(double opacityVal, int duration_msec)
{
    m_opacity->setOpacity(opacityVal);
    m_animation->setDuration(duration_msec);
}

/*
    设置按钮可见性,附带动画
*/
void picButton::setBtnVisible(bool isVisible)
{
    m_animation->stop();
    if(isVisible)
    {
        m_animation->setStartValue(0);
        m_animation->setEndValue(1);
    }
    else
    {
        m_animation->setStartValue(1);
        m_animation->setEndValue(0);
    }
    m_animation->start();
}

bool picButton::event(QEvent *e)
{
    switch(e->type())
    {
        case QEvent::Enter:
            setHover();
            break;
        case QEvent::Leave:
            setNormal();
            break;
        case QEvent::MouseButtonPress:
            setClicked();
            break;
        case QEvent::MouseButtonRelease:
            setHover();
            emit btnClicked();
            break;
        default:
            break;
    }
    return QPushButton::event(e);
}

double picButton::opacity() const
{
    return Opacity;
}

void picButton::initUI()
{
    m_opacity = new QGraphicsOpacityEffect(this);
    m_opacity->setOpacity(0.5);
    //为当前对象按钮设置图形效果
    this->setGraphicsEffect(m_opacity);

    //设置动画过渡
    m_animation = new QPropertyAnimation(m_opacity,"opacity",this);
    m_animation->setEasingCurve(QEasingCurve::Linear);
    m_animation->setDuration(500);//持续时间

}

void picButton::setNormal()
{
    QPixmap tmp;
    tmp.load(m_normal);
    this->setIcon(tmp);
}

void picButton::setHover()
{
    QPixmap tmp;
    tmp.load(m_hover);
    this->setIcon(tmp);
}

void picButton::setClicked()
{
    QPixmap tmp;
    tmp.load(m_clicked);
    this->setIcon(tmp);
}
