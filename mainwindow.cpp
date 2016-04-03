#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "scene.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    auto actionsGroup = new QActionGroup(this);
    actionsGroup->setExclusive(true);
    actionsGroup->addAction(ui->actionNode);
    actionsGroup->addAction(ui->actionEdge);

    auto scene = new Scene(this);
    ui->graphEditor->setScene(scene);
}

MainWindow::~MainWindow()
{
    delete ui;
}
