/********************************************************************************
** Form generated from reading UI file 'mymenu.ui'
**
** Created by: Qt User Interface Compiler version 6.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYMENU_H
#define UI_MYMENU_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MyMenu
{
public:
    QAction *openFileAction;
    QAction *showToolAction;
    QWidget *centralwidget;
    QMenuBar *menubar;
    QMenu *menu;
    QMenu *menu_2;
    QStatusBar *statusbar;
    QDockWidget *dockWidget;
    QWidget *dockWidgetContents;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLineEdit *dockLineEdit;
    QPushButton *closeTool_Btn;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MyMenu)
    {
        if (MyMenu->objectName().isEmpty())
            MyMenu->setObjectName("MyMenu");
        MyMenu->resize(800, 600);
        openFileAction = new QAction(MyMenu);
        openFileAction->setObjectName("openFileAction");
        showToolAction = new QAction(MyMenu);
        showToolAction->setObjectName("showToolAction");
        centralwidget = new QWidget(MyMenu);
        centralwidget->setObjectName("centralwidget");
        MyMenu->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MyMenu);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 25));
        menu = new QMenu(menubar);
        menu->setObjectName("menu");
        menu_2 = new QMenu(menubar);
        menu_2->setObjectName("menu_2");
        MyMenu->setMenuBar(menubar);
        statusbar = new QStatusBar(MyMenu);
        statusbar->setObjectName("statusbar");
        MyMenu->setStatusBar(statusbar);
        dockWidget = new QDockWidget(MyMenu);
        dockWidget->setObjectName("dockWidget");
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName("dockWidgetContents");
        verticalLayout = new QVBoxLayout(dockWidgetContents);
        verticalLayout->setObjectName("verticalLayout");
        label = new QLabel(dockWidgetContents);
        label->setObjectName("label");
        label->setStyleSheet(QString::fromUtf8("background:rgb(170, 255, 255)"));

        verticalLayout->addWidget(label);

        dockLineEdit = new QLineEdit(dockWidgetContents);
        dockLineEdit->setObjectName("dockLineEdit");

        verticalLayout->addWidget(dockLineEdit);

        closeTool_Btn = new QPushButton(dockWidgetContents);
        closeTool_Btn->setObjectName("closeTool_Btn");

        verticalLayout->addWidget(closeTool_Btn);

        dockWidget->setWidget(dockWidgetContents);
        MyMenu->addDockWidget(Qt::LeftDockWidgetArea, dockWidget);
        toolBar = new QToolBar(MyMenu);
        toolBar->setObjectName("toolBar");
        MyMenu->addToolBar(Qt::TopToolBarArea, toolBar);

        menubar->addAction(menu->menuAction());
        menubar->addAction(menu_2->menuAction());
        menu->addAction(openFileAction);
        menu_2->addAction(showToolAction);

        retranslateUi(MyMenu);

        QMetaObject::connectSlotsByName(MyMenu);
    } // setupUi

    void retranslateUi(QMainWindow *MyMenu)
    {
        MyMenu->setWindowTitle(QCoreApplication::translate("MyMenu", "MainWindow", nullptr));
        openFileAction->setText(QCoreApplication::translate("MyMenu", "\346\211\223\345\274\200", nullptr));
        showToolAction->setText(QCoreApplication::translate("MyMenu", "\346\230\276\347\244\272", nullptr));
        menu->setTitle(QCoreApplication::translate("MyMenu", "\346\226\207\344\273\266(&F)", nullptr));
        menu_2->setTitle(QCoreApplication::translate("MyMenu", "\345\267\245\345\205\267(&T)", nullptr));
        label->setText(QCoreApplication::translate("MyMenu", "\350\277\231\346\230\257\345\267\245\345\205\267\347\256\261", nullptr));
        closeTool_Btn->setText(QCoreApplication::translate("MyMenu", "\345\205\263\351\227\255\345\267\245\345\205\267\347\256\261", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("MyMenu", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MyMenu: public Ui_MyMenu {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYMENU_H
