#include "dialog.h"

#include <QApplication>
#include "mymenu.h"
#include "mytextedit.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // std::shared_ptr<Dialog> login = std::make_shared<Dialog>();
    // login->initSignal();
    // login->show();

    // MyMenu window = MyMenu();

    MyTextEdit window = MyTextEdit();
    window.show();
    return a.exec();
}
