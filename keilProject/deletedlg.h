#ifndef DELETEDLG_H
#define DELETEDLG_H

#include <QDialog>
#include "config.h"


namespace Ui {
class DeleteDlg;
}

class DeleteDlg : public QDialog
{
    Q_OBJECT

public:
    explicit DeleteDlg(QWidget *parent = nullptr);
    ~DeleteDlg();
    int exec() override;  // 自定义的 exec 方法，返回 DeleteType

private slots:
    void on_deleteBtn_clicked();
    void on_removeBtn_clicked();
    void on_cancelBtn_clicked();

private:
    Ui::DeleteDlg *ui;
    DeleteType type;
};

#endif // DELETEDLG_H
