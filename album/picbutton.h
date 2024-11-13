#ifndef PICBUTTON_H
#define PICBUTTON_H

#include <QPushButton>
#include <QEvent>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>


class picButton : public QPushButton
{
    Q_OBJECT
    Q_PROPERTY(int opacity READ opacity WRITE setOpacity)
public:
    picButton(QWidget *parent = nullptr) ;
    void setIcons(QString& normal ,QString& hover,QString& clicked);
    void setOpacity(double op);
    void setAnimation(double opacityVal,int duration_msec);
    void setBtnVisible(bool isVisible);
protected:
    bool event(QEvent *e) override;
private:
    //存放图标路径
    QString m_normal;
    QString m_hover;
    QString m_clicked;
    //透明度
    double Opacity;
    double opacity() const;
    QGraphicsOpacityEffect* m_opacity;
    QPropertyAnimation* m_animation;
    void initUI(void);
    void setNormal(void);
    void setHover(void);
    void setClicked(void);
};

#endif // PICBUTTON_H
