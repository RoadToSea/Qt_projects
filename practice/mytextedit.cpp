#include "mytextedit.h"
#include "ui_mytextedit.h"
#include <QTextDocument>
#include <QTextFrame>
#include <QDebug>
#include <QAction>
#include <QTextCursor>
#include <QTextFrameFormat>
#include <QBrush>

void MyTextEdit::slot_print()
{
    QTextDocument* document =ui->textEdit->document();
    QTextFrame* rootframe = document->rootFrame();
    for(auto iter = rootframe->begin();iter!=rootframe->end();++iter)
    {
        qDebug()<<iter.currentBlock().text();
    }

    QTextCursor cursor = document->find("Hello",0,QTextDocument::FindCaseSensitively);
    if(!cursor.isNull())
    {
        QTextFrameFormat format ;
        format.setBorder(2);
        format.setBackground(QBrush(Qt::darkCyan));
        format.setMargin(5);
        format.setPadding(5);
        format.setBorderStyle(QTextFrameFormat::BorderStyle_Dotted);
        cursor.insertFrame(format);
    }
}

MyTextEdit::MyTextEdit(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MyTextEdit)
{
    ui->setupUi(this);
    QAction* printMes = new QAction("打印信息");
    connect(printMes,&QAction::triggered,this,&MyTextEdit::slot_print);
    ui->toolBar->addAction(printMes);


}

MyTextEdit::~MyTextEdit()
{
    delete ui;
}


