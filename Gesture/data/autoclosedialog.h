#ifndef AUTOCLOSEDIALOG_H
#define AUTOCLOSEDIALOG_H

#include <QDialog>
#include <QObject>
#include "ui_autoclosedialog.h"

class AutoCloseDialog : public QDialog
{
    Q_OBJECT
public:
    AutoCloseDialog(QWidget *parent = nullptr);
    ~AutoCloseDialog();
    void setMsg(QString msg);
private:
    Ui::AutoCloseDialog ui;  // 用来访问 UI 元素
    QTimer* m_timer;
private slots:
    void slot_closeDlg();
};

#endif // AUTOCLOSEDIALOG_H
