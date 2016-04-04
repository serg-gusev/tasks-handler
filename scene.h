#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>

class Scene : public QGraphicsScene
{
public:
    Scene(QObject *parent = nullptr);

protected:
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *e) override;
};

#endif // SCENE_H
