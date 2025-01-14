#ifndef CONTROL_H
#define CONTROL_H

#include "helpdlg.h"
#include <QDialog>

namespace Ui {
class Control;
}

class Control : public QWidget
{
    Q_OBJECT

public:
    explicit Control(QWidget *parent = nullptr);
    ~Control();
    void showTips(QString msg);


private:
    Ui::Control *ui;
    QString keilPath;
    QString filePath;
    QString keilTag;;
    helpDlg * helper;
    QTimer* timer;
private slots:
    void on_keilBtn_clicked();

    void on_fileBtn_clicked();

    void on_importBtn_clicked();

    void on_projectLineEdit_editingFinished();

    void on_helpBtn_clicked();

    void clearTips(void);

    void slot_stateChanged(int state);
signals:
    void sign_keilPath(QString& path);
    void sign_import(void);
    void sign_addIncChange(bool flag);
};

#endif // CONTROL_H
