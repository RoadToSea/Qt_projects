#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileSystemModel>
#include <QTreeView>
#include <QListView>
#include <QDir>
#include <QSplitter>
#include <QString>
#include <QPushButton>
#include <QStandardItemModel>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // QFileSystemModel* model = new QFileSystemModel(this);
    // model->setRootPath(QDir::currentPath());

    // QTreeView* tview = new QTreeView(this);
    // tview->setModel(model);
    // tview->setRootIndex(model->index(QDir::currentPath()));

    // setCentralWidget(tview);

    // model =new QStringListModel(this);
    // ui->listView->setModel(model);

    // connect(ui->pushButton,&QPushButton::clicked,this,&MainWindow::addItem);

    QStandardItemModel* model = new QStandardItemModel(this);
    QStandardItem* root = model->invisibleRootItem();

    QStandardItem* item1 = new QStandardItem("节点1");
    QPixmap icon(50,50);
    icon.fill(Qt::blue);
    item1->setData(icon,Qt::DecorationRole);
    root->appendRow(item1);

    root= item1;

    QStandardItem* item2 = new QStandardItem();
    item2->setData("节点2",Qt::EditRole);
    root->appendRow(item2);

    QStandardItem* item3 = new QStandardItem;
    item3->setData("节点3",Qt::EditRole);
    QPixmap pixmap3(50,50);
    pixmap3.fill(Qt::green);
    item3->setData(QIcon(pixmap3), Qt::DecorationRole);
    item3->setData("index3",Qt::ToolTipRole);
    root->appendRow(item3);

    QTreeView* view = new QTreeView(this);
    view->resize(1000,800);
    view->setModel(model);
    view->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addItem()
{
    static unsigned index = 0;
    QString temp = QString("index:%1").arg(index++);
    QStringList strings = model->stringList();
    strings<<temp;
    model->setStringList(strings);
}
