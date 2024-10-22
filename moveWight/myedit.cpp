#include "myedit.h"
#include <QEvent>


myEdit::myEdit(QWidget* parent):QLineEdit(parent) {

}

bool myEdit::event(QEvent *ev)
{
    if(ev->type() == QEvent::KeyPress)
    {
        qDebug()<<"myEdit key pressd ";
    }
    return QLineEdit::event(ev);
}

bool myEdit::eventFilter(QObject *obj, QEvent *ev)
{
    if(obj == this)
    {
        if(ev->type() == QEvent::KeyPress)
        {
            qDebug()<<"myEdit eventFilter enter";

        }
    }
    return QLineEdit::eventFilter(obj,ev);
}
