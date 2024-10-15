#include "wight.h"

wight::wight(QWidget *parent)
    : QWidget{parent}
    : ui(new Ui::Wight)
{


}

void wight::setLogin(const std::weak_ptr<Dialog> &wp)
{
    pdialog =wp;
}
