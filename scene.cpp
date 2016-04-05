#include "scene.h"
#include "node.h"

#include <QGraphicsSceneMouseEvent>
#include <QDebug>

Scene::Scene(MainWindow *parent) :
    QGraphicsScene(parent),
    _mainWindow(parent)
{
    setSceneRect(0, 0, 800, 600);
}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent *e)
{
    QGraphicsScene::mousePressEvent(e);
    _pressed = true;
}

void Scene::mouseReleaseEvent(QGraphicsSceneMouseEvent *e)
{
    if (_pressed) {
        auto node = new Node;
        auto nodeRect = node->boundingRect();
        node->setPos(e->scenePos() - QPointF(nodeRect.width() / 2, nodeRect.height() / 2));
        addItem(node);
    }

    _pressed = false;

    QGraphicsScene::mouseReleaseEvent(e);
}

