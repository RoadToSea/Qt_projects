/********************************************************************************
** Form generated from reading UI file 'mytextedit.ui'
**
** Created by: Qt User Interface Compiler version 6.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYTEXTEDIT_H
#define UI_MYTEXTEDIT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MyTextEdit
{
public:
    QWidget *centralwidget;
    QTextEdit *textEdit;
    QMenuBar *menubar;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MyTextEdit)
    {
        if (MyTextEdit->objectName().isEmpty())
            MyTextEdit->setObjectName("MyTextEdit");
        MyTextEdit->resize(800, 600);
        centralwidget = new QWidget(MyTextEdit);
        centralwidget->setObjectName("centralwidget");
        textEdit = new QTextEdit(centralwidget);
        textEdit->setObjectName("textEdit");
        textEdit->setGeometry(QRect(100, 90, 541, 371));
        textEdit->setStyleSheet(QString::fromUtf8("border: 2px solid rgb(68, 204, 204)"));
        MyTextEdit->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MyTextEdit);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 25));
        MyTextEdit->setMenuBar(menubar);
        statusbar = new QStatusBar(MyTextEdit);
        statusbar->setObjectName("statusbar");
        MyTextEdit->setStatusBar(statusbar);
        toolBar = new QToolBar(MyTextEdit);
        toolBar->setObjectName("toolBar");
        MyTextEdit->addToolBar(Qt::TopToolBarArea, toolBar);

        retranslateUi(MyTextEdit);

        QMetaObject::connectSlotsByName(MyTextEdit);
    } // setupUi

    void retranslateUi(QMainWindow *MyTextEdit)
    {
        MyTextEdit->setWindowTitle(QCoreApplication::translate("MyTextEdit", "MainWindow", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("MyTextEdit", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MyTextEdit: public Ui_MyTextEdit {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYTEXTEDIT_H
