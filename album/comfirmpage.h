#ifndef COMFIRMPAGE_H
#define COMFIRMPAGE_H

#include <QWizardPage>

namespace Ui {
class Comfirmpage;
}

class Comfirmpage : public QWizardPage
{
    Q_OBJECT

public:
    explicit Comfirmpage(QWidget *parent = nullptr);
    ~Comfirmpage();

private:
    Ui::Comfirmpage *ui;
};

#endif // COMFIRMPAGE_H
