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
protected:
    bool eventFilter(QObject *object, QEvent *event) override;
private:
    Ui::PortrayPic *ui;
    void initUI(void);
};

#endif // PORTRAYPIC_H
