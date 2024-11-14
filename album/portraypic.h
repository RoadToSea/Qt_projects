#ifndef PORTRAYPIC_H
#define PORTRAYPIC_H

#include <QDialog>

namespace Ui {
class PortrayPic;
}

class PortrayPic : public QDialog
{
    Q_OBJECT
signals:
    void showPrePic(void);
    void showNextPic(void);
public slots:
    void slot_showPic(QString& picPath);
    void slot_prePic(void);
    void slot_nextPic(void);
public:
    explicit PortrayPic(QWidget *parent = nullptr);
    ~PortrayPic();
protected:
    bool eventFilter(QObject *object, QEvent *event) override;
private:
    Ui::PortrayPic *ui;
    QPixmap m_pixmap;
    void initUI(void);
};

#endif // PORTRAYPIC_H
