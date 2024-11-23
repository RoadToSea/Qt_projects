#include "slideStateButton.h"
#include "qcoreevent.h"
using namespace album;

slideStateButton::slideStateButton(QWidget *parent):QPushButton(parent),m_state(true)
{

}

bool slideStateButton::event(QEvent *e)
{
    switch(e->type())
    {
        case QEvent::Enter:
            if(m_state)
                setStateIcon(album::playHover);
            else
                setStateIcon(album::stopHover);
        break;

        case QEvent::Leave:
            if(m_state)
                setStateIcon(album::playNormal);
            else
                setStateIcon(album::stopNormal);
            break;
        case QEvent::MouseButtonPress:
            if(m_state)
                setStateIcon(album::playPress);
            else
                setStateIcon(album::stopPress);
            break;
        case QEvent::MouseButtonRelease:
            if(m_state)
            {
                setStateIcon(album::stopHover);
                emit sigStart();
            }
            else
            {
                setStateIcon(album::playHover);
                emit sigStop();
            }
            m_state = !m_state;
            break;
        default:
            break;
    }
        return QPushButton::event(e);
}

void slideStateButton::setIcons(QString playNormal, QString playHover, QString playPress,
              QString stopNormal, QString stopHover, QString stopPress) {
    m_playNormal = playNormal;
    m_playHover = playHover;
    m_playPress = playPress;
    m_stopNormal = stopNormal;
    m_stopHover = stopHover;
    m_stopPress = stopPress;

    QPixmap pix(m_playNormal);
    this->setIcon(pix);
    this->setIconSize(pix.size());
    this->resize(pix.size());
}

void slideStateButton::setStateIcon(album::buttonState state)
{
    QPixmap pix;

    switch (state) {
    case album::playNormal:
        pix.load(m_playNormal);
        break;
    case album::playHover:
        pix.load(m_playHover);
        break;
    case album::playPress:
        pix.load(m_playPress);
        break;
    case album::stopNormal:
        pix.load(m_stopNormal);
        break;
    case album::stopHover:
        pix.load(m_stopHover);
        break;
    case album::stopPress:
        pix.load(m_stopPress);
        break;
    default:
        qWarning("Invalid state passed to setState");
        return;
    }
    qDebug()<<"state:"<<state;
    // 设置按钮图标和大小
    if (!pix.isNull()) {
        this->setIcon(pix);
        this->setIconSize(pix.size());
        this->resize(pix.size());
    } else {
        qWarning("Failed to load pixmap for the given state");
    }
}

bool &slideStateButton::getState()
{
    return m_state;
}


