#include "scene.h"
#include "node.h"

#include <QGraphicsSceneMouseEvent>

Scene::Scene(QObject *parent) :
    QGraphicsScene(parent)
{
    setSceneRect(0, 0, 800, 600);
}

void Scene::setNodesInteractable(bool interactable)
{
    _nodesInteractable = interactable;
    for (auto item : items()) {
        auto nodeItem = dynamic_cast<Node *>(item);
        if (nodeItem) {
            nodeItem->setInteractable(interactable);
        }
    }
}

void Scene::mouseReleaseEvent(QGraphicsSceneMouseEvent *e)
{
    bool hoverItem = itemAt(e->scenePos(), QTransform());
    if (!hoverItem && _nodesInteractable) {
        auto node = new Node;
        node->setInteractable(_nodesInteractable);
        node->setSelected(true);
        auto nodeRect = node->boundingRect();
        node->setPos(e->scenePos() - QPointF(nodeRect.width() / 2, nodeRect.height() / 2));
        addItem(node);
    }

    QGraphicsScene::mouseReleaseEvent(e);
}
