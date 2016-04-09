#ifndef NODE_H
#define NODE_H

#include <QGraphicsEllipseItem>
#include <QTimer>

class Edge;

class Node : public QGraphicsEllipseItem
{
public:
    Node();

    void paint(QPainter *p, const QStyleOptionGraphicsItem *o, QWidget *w = nullptr) override;

    void setInteractable(bool interactable);

    void addInEdge(Edge *edge);
    void addOutEdge(Edge *edge);
    void removeInEdge(Edge *edge);
    void removeOutEdge(Edge *edge);

    void adjustEdges();

protected:
    QVariant itemChange(GraphicsItemChange c, const QVariant &v) override;
    void keyPressEvent(QKeyEvent *e) override;

private:
    int _number = 1;
    QTimer _inputTimer;

    QList<Edge *> _inEdges;
    QList<Edge *> _outEdges;
};

#endif // NODE_H
