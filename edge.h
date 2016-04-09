#ifndef EDGE_H
#define EDGE_H

#include <QGraphicsLineItem>

class Node;

class Edge : public QGraphicsLineItem
{
public:
    Edge(Node *startNode);
    ~Edge();

    void paint(QPainter *p, const QStyleOptionGraphicsItem *o, QWidget *w = nullptr) override;

    void adjust();
    void setEndPoint(const QPointF &point);
    void setEndNode(Node *endNode);

private:
    Node *_startNode = nullptr;
    Node *_endNode = nullptr;

    QPointF _endPoint;

    const int _arrowSize = 10;
};

#endif // EDGE_H
