#ifndef CLOSEPRODIALOG_H
#define CLOSEPRODIALOG_H

#include <QDialog>


namespace Ui {
class CloseProDialog;
}

class CloseProDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CloseProDialog(QWidget *parent = nullptr);
    ~CloseProDialog();
    bool& isDelete(void);

private slots:
    void on_isDeleteCheckBox_stateChanged(int arg1);

private:
    Ui::CloseProDialog *ui;
    bool m_isDelete;
};

#endif // CLOSEPRODIALOG_H
