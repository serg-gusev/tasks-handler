#include "scene.h"
#include "node.h"

#include <QGraphicsSceneMouseEvent>
#include <QDebug>

Scene::Scene(QObject *parent) :
    QGraphicsScene(parent)
{
    //setSceneRect(0, 0, 800, 600);
}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent *e)
{

}

void Scene::mouseReleaseEvent(QGraphicsSceneMouseEvent *e)
{
    qDebug() << "mouse release" << e->pos();
    auto node = new Node;
    node->setPos(e->pos());
    addItem(node);

    QGraphicsScene::mouseReleaseEvent(e);
}

