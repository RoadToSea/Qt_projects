#ifndef PICBUTTON_H
#define PICBUTTON_H

#include <QPushButton>

class picButton : public QPushButton
{
public:
    picButton(QWidget *parent = nullptr) ;
    void setIcons(QString& );
};

#endif // PICBUTTON_H
