#include "myedit.h"
#include <QEvent>


myEdit::myEdit(QWidget* parent):QLineEdit(parent) {}

bool myEdit::event(QEvent *ev)
{
    if(ev->type() == QEvent::KeyPress)
    {
        qDebug()<<"myEdit key pressd ";
    }
    return QLineEdit::event(ev);
}
