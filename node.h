#ifndef NODE_H
#define NODE_H

#include <QGraphicsEllipseItem>
#include <QTimer>

class Node : public QGraphicsEllipseItem
{
public:
    Node();

    void paint(QPainter *p, const QStyleOptionGraphicsItem *o, QWidget *w = nullptr) override;

protected:
//    void mousePressEvent(QGraphicsSceneMouseEvent *e) override;
//    void mouseMoveEvent(QGraphicsSceneMouseEvent *e) override;
//    void mouseReleaseEvent(QGraphicsSceneMouseEvent *e) override;
    void keyPressEvent(QKeyEvent *e) override;

private:
    int _number = 1;
    QTimer _inputTimer;

    bool _dragged = false;
    QPointF _dragPoint;
};

#endif // NODE_H
