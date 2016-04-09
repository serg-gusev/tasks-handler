#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include "edge.h"

class Scene : public QGraphicsScene
{
public:
    Scene(QObject *parent = nullptr);

    void setNodesInteractable(bool interactable);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *e) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *e) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *e) override;

private:
    bool _nodesInteractable = true;
    Edge *_currentEdge = nullptr;
};

#endif // SCENE_H
