#ifndef REGIST_H
#define REGIST_H

#include <QDialog>

class Dialog;

namespace Ui {
class regist;
}

class regist : public QDialog
{
    Q_OBJECT

public:
    explicit regist(QWidget *parent = nullptr);
    ~regist();
    void setLogin(const std::weak_ptr<Dialog>& wp);

private:
    Ui::regist *ui;
    std::weak_ptr<Dialog> pdialog;
};

#endif // REGIST_H
