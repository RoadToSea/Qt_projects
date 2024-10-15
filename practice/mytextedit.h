#ifndef MYTEXTEDIT_H
#define MYTEXTEDIT_H

#include <QMainWindow>

namespace Ui {
class MyTextEdit;
}

class MyTextEdit : public QMainWindow
{
    Q_OBJECT
public slots:
    void slot_print();

public:
    explicit MyTextEdit(QWidget *parent = nullptr);
    ~MyTextEdit();

private:
    Ui::MyTextEdit *ui;
};

#endif // MYTEXTEDIT_H
