#include "scene.h"
#include "node.h"

#include <QGraphicsSceneMouseEvent>
#include <QDebug>

Scene::Scene(QObject *parent) :
    QGraphicsScene(parent)
{
    setSceneRect(0, 0, 800, 600);
}

void Scene::mouseReleaseEvent(QGraphicsSceneMouseEvent *e)
{
    auto node = new Node;
    auto nodeRect = node->boundingRect();
    node->setPos(e->scenePos() - QPointF(nodeRect.width() / 2, nodeRect.height() / 2));
    addItem(node);

    QGraphicsScene::mouseReleaseEvent(e);
}

