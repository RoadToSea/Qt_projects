#ifndef SLIDEDLG_H
#define SLIDEDLG_H

#include <QDialog>
#include "QTreeWidgetItem"


namespace Ui {
class SlideDlg;
}

class SlideDlg : public QDialog
{
    Q_OBJECT

public:
    explicit SlideDlg(QWidget *parent = nullptr);
    ~SlideDlg();
    void setPicItem(QTreeWidgetItem* firstItem,QTreeWidgetItem* lastItem);
    void play();
    void stop();

private:
    Ui::SlideDlg *ui;
    QTreeWidgetItem* m_firstItem;
    QTreeWidgetItem* m_lastItem;
};

#endif // SLIDEDLG_H
