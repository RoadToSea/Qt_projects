#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "myedit.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
protected:
    bool eventFilter(QObject *obj, QEvent *ev) override;

private:
    Ui::Widget *ui;
    myEdit* edit;
};
#endif // WIDGET_H
