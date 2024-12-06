#ifndef CONTROLWID_H
#define CONTROLWID_H

#include <QWidget>

namespace Ui {
class ControlWid;
}

class ControlWid : public QWidget
{
    Q_OBJECT

public:
    explicit ControlWid(QWidget *parent = nullptr);
    ~ControlWid();

private:
    Ui::ControlWid *ui;
    bool m_status;

signals:
    void sig_acLabelChange(const QString& label);
    void sig_startStore();
    void sig_stopStore();
private slots:
    void slot_acLabel(int index);
    void slot_storeFlag();
};

#endif // CONTROLWID_H
