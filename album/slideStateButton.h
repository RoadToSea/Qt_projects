#ifndef SLIDESTATEBUTTON_H
#define SLIDESTATEBUTTON_H

#include <QPushButton>
#include "config.h"

using namespace album ;

class slideStateButton : public QPushButton
{
public:
    slideStateButton(QWidget *parent);
    bool event(QEvent *e) override;
    void setIcons(QString playNormal, QString playHover, QString playPress,
                  QString stopNormal, QString stopHover, QString stopPress);
    void setStateIcon(album::buttonState state);
    bool& getState(void);

private:
    QString m_playNormal;
    QString m_playHover;
    QString m_playPress;
    QString m_stopNormal;
    QString m_stopHover;
    QString m_stopPress;
    //状态0: 暂停,  状态1:  播放
    bool  m_state;
};

#endif // SLIDESTATEBUTTON_H
