#include "mainwindow.h"
#include "./ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QFont font;
    font.setFamily("Courier");
    font.setFixedPitch(true);
    font.setPointSize(10);

    codeEdit = new CodeEditor();
    codeEdit->setFont(font);

    highlighter = new Highlighter(codeEdit->document());
    setCentralWidget(codeEdit);
}

MainWindow::~MainWindow()
{
    delete ui;
}
