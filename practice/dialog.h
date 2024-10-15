#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "regist.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Dialog;
}
QT_END_NAMESPACE

class Dialog : public QDialog,public std::enable_shared_from_this<Dialog>
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    void initSignal(void);
    void consol(void);
    ~Dialog();

private slots:

    void on_registerBtn_clicked();

    void on_loginBtn_clicked();

private:
    Ui::Dialog *ui;
    std::shared_ptr<regist> pregist;
};
#endif // DIALOG_H
