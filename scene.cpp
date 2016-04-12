#include "scene.h"
#include "node.h"

#include <QGraphicsSceneMouseEvent>
#include <QDebug>

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

Graph Scene::buildGraph() const
{
    Graph g;

    for (auto item : items()) {
        auto node = dynamic_cast<Node *>(item);
        if (node) {
            GraphNode graphNode;
            graphNode.index = node->index();
            graphNode.weight = node->number();
            g.addNode(graphNode);
        }
    }

    for (auto item : items()) {
        auto edge = dynamic_cast<Edge *>(item);
        if (edge) {
            auto &startGraphNode = g[edge->startNode()->index()];
            auto &endGraphNode = g[edge->endNode()->index()];

            if (startGraphNode.index != 0 && endGraphNode.index != 0) {
                endGraphNode.addParent(startGraphNode.index);
            }
        }
    }

    return g;
}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent *e)
{
    if (!_nodesInteractable) {
        auto item = itemAt(e->scenePos(), QTransform());
        auto nodeItem = dynamic_cast<Node *>(item);
        if (nodeItem) {
            _currentEdge = new Edge(nodeItem);
            addItem(_currentEdge);
        }
    }

    QGraphicsScene::mousePressEvent(e);
}

void Scene::mouseMoveEvent(QGraphicsSceneMouseEvent *e)
{
    if (!_nodesInteractable && _currentEdge) {
        _currentEdge->setEndPoint(e->scenePos());
    }

    QGraphicsScene::mouseMoveEvent(e);
}

void Scene::mouseReleaseEvent(QGraphicsSceneMouseEvent *e)
{
    auto hoverItem = itemAt(e->scenePos(), QTransform());
    if (!hoverItem && _nodesInteractable) {
        auto node = new Node;
        node->setInteractable(_nodesInteractable);
        node->setSelected(true);
        node->setPos(e->scenePos());
        addItem(node);
    } else if (!_nodesInteractable && _currentEdge) {
        auto nodeItem = dynamic_cast<Node *>(hoverItem);
        if (nodeItem) {
            _currentEdge->setEndNode(nodeItem);
        } else {
            removeItem(_currentEdge);
            delete _currentEdge;
        }
        _currentEdge = nullptr;
    }

    QGraphicsScene::mouseReleaseEvent(e);
}
