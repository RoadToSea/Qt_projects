#ifndef PJTREE_H
#define PJTREE_H

#include <QDialog>

namespace Ui {
class PjTree;
}

class PjTree : public QWidget
{
    Q_OBJECT

public:
    explicit PjTree(QWidget *parent = nullptr);
    ~PjTree();

private:
    Ui::PjTree *ui;
public slots:
    void slot_PjChanged(void);
    void slot_addInc(bool flag);
};

#endif // PJTREE_H
