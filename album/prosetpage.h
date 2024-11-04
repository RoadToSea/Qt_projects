#ifndef PROSETPAGE_H
#define PROSETPAGE_H

#include <QWizardPage>

namespace Ui {
class Prosetpage;
}

class Prosetpage : public QWizardPage
{
    Q_OBJECT

public:
    explicit Prosetpage(QWidget *parent = nullptr);
    bool isComplete() const override;
    void getSettings(QString& name,QString& path);
    ~Prosetpage();

private slots:
    void on_Pb_Brower_clicked();

private:
    Ui::Prosetpage *ui;
};

#endif // PROSETPAGE_H
