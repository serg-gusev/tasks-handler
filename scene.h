#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>

class Scene : public QGraphicsScene
{
public:
    Scene(QObject *parent = nullptr);

    void setNodesInteractable(bool interactable);

protected:
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *e) override;

private:
    bool _nodesInteractable = true;
};

#endif // SCENE_H
