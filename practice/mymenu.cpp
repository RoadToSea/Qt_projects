#include "mymenu.h"
#include "ui_mymenu.h"
#include <QMenu>
#include <QAction>
#include <QDebug>
#include "myaction.h"
#include <QActionGroup>
#include <QList>
#include <QToolButton>

MyMenu::MyMenu(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MyMenu)
{
    ui->setupUi(this);
    QMenu* edit = new QMenu("编辑(&E)",this);
    ui->menubar->addMenu(edit);
    edit->addSeparator();
    QAction* Action_changeFile = new QAction(tr("改变文件"));
    Action_changeFile->setShortcut(QKeySequence::Open);
    edit->addAction(Action_changeFile);
    connect(Action_changeFile,&QAction::triggered,this,&MyMenu::on_changeFile_triggered);

    edit->addSeparator();
    MyAction* Action_input = new MyAction(this);
    edit->addAction(Action_input);
    connect(Action_input,&MyAction::signal_getText,ui->dockLineEdit,&QLineEdit::setText);

    QAction* Action_showInfo= new QAction("显示提示");
    QLabel* permanentInfo = new QLabel("这是永久提示信息");
    ui->statusbar->addPermanentWidget(permanentInfo);
    ui->toolBar->addAction(Action_showInfo);
    connect(Action_showInfo,&QAction::triggered,this,&MyMenu::slot_showInfo);

    QAction* Action1 = new QAction("action1");
    QAction* Action2 = new QAction("action2");
    QAction* Action3 = new QAction("action3");
    QAction* Action4 = new QAction("action4");
    QList<QAction*> actionList ;
    actionList.append(Action1);
    actionList.append(Action2);
    actionList.append(Action3);
    actionList.append(Action4);
    ui->toolBar->addActions(actionList);

    QToolButton * toolBtn = new QToolButton(this);
    toolBtn->setText(tr("颜色"));
    QMenu* colorMenu = new QMenu(this);
    colorMenu->addAction(tr("红色"));
    colorMenu->addAction(tr("绿色"));
    toolBtn->setMenu(colorMenu);
    toolBtn->setPopupMode(QToolButton::MenuButtonPopup);
    ui->toolBar->addWidget(toolBtn);
}

MyMenu::~MyMenu()
{
    delete ui;
}



void MyMenu::on_closeTool_Btn_clicked()
{
    ui->dockWidget->close();
}


void MyMenu::on_showToolAction_triggered()
{
    ui->dockWidget->show();
}

void MyMenu::on_changeFile_triggered()
{
    qDebug()<<"改变文件";
}

void MyMenu::slot_showInfo()
{
    ui->statusbar->showMessage("这是提示信息",4000);
}



