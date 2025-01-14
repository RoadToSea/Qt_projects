#ifndef HELPDLG_H
#define HELPDLG_H

#include <QDialog>

namespace Ui {
class helpDlg;
}

class helpDlg : public QDialog
{
    Q_OBJECT

public:
    explicit helpDlg(QWidget *parent = nullptr);
    void loadMarkdown(QString path);
    ~helpDlg();

private:
    Ui::helpDlg *ui;
    QString markdown;
};

#endif // HELPDLG_H
