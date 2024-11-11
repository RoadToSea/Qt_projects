#ifndef PORTRAYPIC_H
#define PORTRAYPIC_H

#include <QDialog>

namespace Ui {
class PortrayPic;
}

class PortrayPic : public QDialog
{
    Q_OBJECT

public:
    explicit PortrayPic(QWidget *parent = nullptr);
    ~PortrayPic();

private:
    Ui::PortrayPic *ui;
};

#endif // PORTRAYPIC_H
