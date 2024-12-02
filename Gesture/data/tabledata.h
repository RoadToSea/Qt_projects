#ifndef TABLEDATA_H
#define TABLEDATA_H

#include <QWidget>

namespace Ui {
class TableData;
}

class TableData : public QWidget
{
    Q_OBJECT

public:
    explicit TableData(QWidget *parent = nullptr);
    ~TableData();

private:
    Ui::TableData *ui;
};

#endif // TABLEDATA_H
