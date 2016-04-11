#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    auto actionsGroup = new QActionGroup(this);
    actionsGroup->setExclusive(true);
    actionsGroup->addAction(ui->actionNode);
    actionsGroup->addAction(ui->actionEdge);

    scene = new Scene(this);
    scene->setNodesInteractable(ui->actionNode->isChecked());
    ui->graphEditor->setScene(scene);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNode_triggered()
{
    scene->setNodesInteractable(true);
}

void MainWindow::on_actionEdge_triggered()
{
    scene->setNodesInteractable(false);
}

void MainWindow::on_actionStart_triggered()
{
    auto graph = scene->buildGraph();
    if (graph.isEmpty()) {
        ui->statusBar->showMessage(tr("Error!"));
        return;
    }

    timeline = new Timeline(&graph);
    timeline->show();
}
