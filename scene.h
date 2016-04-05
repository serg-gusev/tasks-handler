#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>

#include "mainwindow.h"

class Scene : public QGraphicsScene
{
public:
    Scene(MainWindow *parent = nullptr);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *e) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *e) override;

private:
    MainWindow *_mainWindow = nullptr;
    bool _pressed = false;
};

#endif // SCENE_H
