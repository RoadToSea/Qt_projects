#ifndef MYEDIT_H
#define MYEDIT_H

#include <QLineEdit>
#include <QObject>

class myEdit : public QLineEdit
{
    Q_OBJECT
public:
    myEdit(QWidget* parent);
    bool event(QEvent* ev) override;
    bool eventFilter(QObject *obj, QEvent *ev) override;
};

#endif // MYEDIT_H
