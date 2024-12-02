#include "tabledata.h"
#include "ui_tabledata.h"

TableData::TableData(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TableData)
{
    ui->setupUi(this);
}

TableData::~TableData()
{
    delete ui;
}
