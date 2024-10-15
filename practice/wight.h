#ifndef WIGHT_H
#define WIGHT_H

#include <QWidget>

namespace Ui {
class Dialog;
}

class Dialog;

class wight : public QWidget
{
    Q_OBJECT
public:
    explicit wight(QWidget *parent = nullptr);
    void setLogin(const std::weak_ptr<Dialog>& wp);

signals:


private:
    Ui::wight *ui;
    std::weak_ptr<Dialog> pdialog;
};

#endif // WIGHT_H
