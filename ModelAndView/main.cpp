#include "mainwindow.h"

#include <QApplication>
#include "stringlistmodel.h"
#include <QListView>
#include <QTreeView>
#include <QStringList>
#include <QTableView>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QStringList list;
    list<<"hello"<<"world"<<"third"<<"line four";
    StringListModel model(list);

    QTreeView tview;
    tview.setModel(static_cast<QAbstractItemModel*>(&model));
    tview.show();

    QListView lview;
    lview.setModel(static_cast<QAbstractItemModel*>(&model));
    lview.show();

    QTableView tableView;
    tableView.setModel(&model);
    tableView.show();

    model.insertRows(3,1);
    model.setData(model.index(3,0),"add item");
    model.removeRows(2,1);
    // MainWindow w;
    // w.show();
    return a.exec();
}
