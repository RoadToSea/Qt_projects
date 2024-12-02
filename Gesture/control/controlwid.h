#ifndef CONTROLWID_H
#define CONTROLWID_H

#include <QWidget>

namespace Ui {
class ControlWid;
}

class ControlWid : public QWidget
{
    Q_OBJECT

public:
    explicit ControlWid(QWidget *parent = nullptr);
    ~ControlWid();

private:
    Ui::ControlWid *ui;
};

#endif // CONTROLWID_H
