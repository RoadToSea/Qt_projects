#include "myaction.h"

void MyAction::setText()
{
    emit signal_getText(lineEdit->text());
}

MyAction::MyAction(QObject *parent):QWidgetAction(parent)
{
    lineEdit = new QLineEdit();
    connect(lineEdit,&QLineEdit::returnPressed,this,&MyAction::setText);
}

QWidget *MyAction::createWidget(QWidget *parent)
{
    if(!(parent->inherits("QMenu")||parent->inherits("QToolBar")))
        return 0;
    QLabel* label = new QLabel("请输入:");
    splitter = new QSplitter(parent);
    splitter->addWidget(label);
    splitter->addWidget(lineEdit);
    return splitter;
}
