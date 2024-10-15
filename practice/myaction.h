#ifndef MYACTION_H
#define MYACTION_H
#include <QWidgetAction>
#include <QObject>
#include <QLineEdit>
#include <QSplitter>
#include <QLabel>

class MyAction:public QWidgetAction
{
    Q_OBJECT
private slots:
    void setText(void);
signals:
    void signal_getText(const QString& str);

public:
    MyAction(QObject* parent = nullptr);
    virtual QWidget *createWidget(QWidget *parent) override;
private:
    QLineEdit* lineEdit;
    QSplitter* splitter;
};

#endif // MYACTION_H
