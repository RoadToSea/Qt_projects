#ifndef SWITCHBTN_H
#define SWITCHBTN_H

#include <QObject>
#include <QPushButton>

class switchBtn : public QPushButton
{
    Q_OBJECT
public:
    switchBtn(QWidget *parent = nullptr);
    ~switchBtn();
    void setSource(QString on,QString off);
    void setStatus(bool flag);
    void reverseStatus(void);


private:
    QIcon* Icon_ON;
    QIcon* Icon_OFF;
    bool status;
private slots:
    void slot_clicked();
};

#endif // SWITCHBTN_H
