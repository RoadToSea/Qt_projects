#ifndef WIZARD_H
#define WIZARD_H

#include <QWizard>

namespace Ui {
class Wizard;
}

class Wizard : public QWizard
{
    Q_OBJECT
signals:
    void finishSetting(const QString& name,const QString& path);

public:
    explicit Wizard(QWidget *parent = nullptr);
    ~Wizard();
    void done(int result) override;
private:
    Ui::Wizard *ui;
};

#endif // WIZARD_H
