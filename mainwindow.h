#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "scene.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionNode_triggered();
    void on_actionEdge_triggered();
    void on_actionStart_triggered();

private:
    Ui::MainWindow *ui;
    Scene *scene = nullptr;
};

#endif // MAINWINDOW_H
