#include "pjtree.h"
#include "ui_pjtree.h"

#include <QFileInfo>
#include "xmlparser.h"


PjTree::PjTree(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PjTree)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_StyledBackground, true); // 启用 QSS
    ui->pjTreeWidget->setSelectionMode(QAbstractItemView::ContiguousSelection);
}


PjTree::~PjTree()
{
    delete ui;
}

void PjTree::slot_PjChanged()
{
    //重新构建文件树
    ui->pjTreeWidget->buildTree(XmlParser::getInstance()->getPjName(),XmlParser::getInstance()->getGpFileName());
}

void PjTree::slot_addInc(bool flag)
{
    ui->pjTreeWidget->setIsAddInc(flag);
}

