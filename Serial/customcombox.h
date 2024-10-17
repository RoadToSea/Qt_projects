#ifndef CUSTOMCOMBOX_H
#define CUSTOMCOMBOX_H

#include <QComboBox>

class customCombox : public QComboBox
{
    Q_OBJECT
signals:
    void pullDownList(void);
public:
    customCombox(QWidget* parent = nullptr);
    virtual void showPopup() override;
};



#endif // CUSTOMCOMBOX_H
