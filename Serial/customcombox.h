#ifndef CUSTOMCOMBOX_H
#define CUSTOMCOMBOX_H

#include <QComboBox>

class customCombox : public QComboBox
{
public:
    customCombox(QWidget* parent = nullptr);
    virtual void showPopup() override;
};



#endif // CUSTOMCOMBOX_H
