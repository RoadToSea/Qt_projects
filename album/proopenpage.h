#ifndef PROOPENPAGE_H
#define PROOPENPAGE_H

#include <QWidget>

class proOpenPage : public QWidget
{
    Q_OBJECT
signals:
    void finishOpenPro(QString& name, QString& path);
public:
    explicit proOpenPage(QWidget *parent = nullptr);
    void openPro(void);

signals:
};

#endif // PROOPENPAGE_H
