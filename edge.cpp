#include "edge.h"
#include "node.h"

#include <cmath>
#include <QPen>
#include <QPainter>
#include <QDebug>

Edge::Edge(Node *startNode) :
    QGraphicsLineItem(),
    _startNode(startNode)
{
    setPen(QPen(Qt::black));

    if (_startNode) {
        setEndPoint(mapFromItem(_startNode, 0, 0));
        _startNode->addOutEdge(this);
    }
}

Edge::~Edge()
{
    if (_startNode) {
        _startNode->removeOutEdge(this);
    }

    if (_endNode) {
        _endNode->removeInEdge(this);
    }
}

void Edge::paint(QPainter *p, const QStyleOptionGraphicsItem *o, QWidget *w)
{
    QGraphicsLineItem::paint(p, o, w);

    if (!_startNode)
        return;

    auto l = line();
    auto angle = std::acos(l.dx() / l.length());
    if (l.dy() >= 0) {
        angle = 2.0 * M_PI - angle;
    }

    QPointF arrowP1, arrowP2;
    if (_endNode) {
        arrowP1 = l.p2() - QPointF(sin(angle + M_PI / 3) * _arrowSize,
                                   cos(angle + M_PI / 3) * _arrowSize);
        arrowP2 = l.p2() - QPointF(sin(angle + M_PI - M_PI / 3) * _arrowSize,
                                   cos(angle + M_PI - M_PI / 3) * _arrowSize);
    } else {
        arrowP1 = _endPoint - QPointF(sin(angle + M_PI / 3) * _arrowSize,
                                      cos(angle + M_PI / 3) * _arrowSize);
        arrowP2 = _endPoint - QPointF(sin(angle + M_PI - M_PI / 3) * _arrowSize,
                                      cos(angle + M_PI - M_PI / 3) * _arrowSize);
    }

    p->setBrush(Qt::black);
    p->drawPolygon(QPolygonF() << l.p2() << arrowP1 << arrowP2);
}

void Edge::adjust()
{
    if (!_startNode)
        return;

    QLineF l;
    if (_endNode) {
        l = QLineF(mapFromItem(_startNode, 0, 0), mapFromItem(_endNode, 0, 0));
    } else {
        l = QLineF(mapFromItem(_startNode, 0, 0), _endPoint);
    }
    auto length = l.length();

    prepareGeometryChange();

    if (length > 30.0) {
        QPointF edgeOffset((l.dx() * 15) / length, (l.dy() * 15) / length);
        setLine(QLineF(l.p1() + edgeOffset, l.p2() - edgeOffset));
    } else {
        setLine(QLineF(l.p1(), l.p1()));
    }

    update();
}

void Edge::setEndPoint(const QPointF &point)
{
    if (_endNode)
        return;

    _endPoint = point;
    adjust();
}

void Edge::setEndNode(Node *endNode)
{
    _endNode = endNode;
    _endNode->addInEdge(this);

    adjust();
}

