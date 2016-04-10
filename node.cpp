#include "node.h"
#include "edge.h"

#include <QPen>
#include <QPainter>
#include <QFont>
#include <QKeyEvent>
#include <QDebug>

int Node::globalNodeIndex = 1;

Node::Node() :
    QGraphicsEllipseItem(-15, -15, 30, 30)
{
    setPen(QPen(Qt::red, 3));
    setFlags(flags() | ItemSendsGeometryChanges);
    setInteractable(true);

    _inputTimer.setInterval(1500);
    _inputTimer.setSingleShot(true);

    _index = globalNodeIndex;
    globalNodeIndex++;
}

void Node::paint(QPainter *p, const QStyleOptionGraphicsItem *o, QWidget *w)
{
    QGraphicsEllipseItem::paint(p, o, w);

    auto f = p->font();

    f.setPixelSize(16);
    p->setFont(f);
    p->setPen(Qt::black);
    p->drawText(boundingRect(), Qt::AlignCenter, QString::number(_number));

    f.setPixelSize(8);
    p->setFont(f);
    p->setPen(Qt::blue);
    p->drawText(boundingRect().translated(3, -3), Qt::AlignRight | Qt::AlignTop, QString::number(_index));
}

void Node::setInteractable(bool interactable)
{
    auto flgs = ItemIsMovable | ItemIsFocusable | ItemIsSelectable;
    setFlags(interactable ? (flags() | flgs) : (flags() & (~flgs)));
}

void Node::addInEdge(Edge *edge)
{
    if (!_inEdges.contains(edge)) {
        _inEdges << edge;
    }
}

void Node::addOutEdge(Edge *edge)
{
    if (!_outEdges.contains(edge)) {
        _outEdges << edge;
    }
}

void Node::removeInEdge(Edge *edge)
{
    _inEdges.removeAll(edge);
}

void Node::removeOutEdge(Edge *edge)
{
    _outEdges.removeAll(edge);
}

void Node::adjustEdges()
{
    for (auto edge : _inEdges) {
        edge->adjust();
    }

    for (auto edge : _outEdges) {
        edge->adjust();
    }
}

QVariant Node::itemChange(QGraphicsItem::GraphicsItemChange c, const QVariant &v)
{
    if (c == ItemPositionChange) {
        adjustEdges();
    }

    return QGraphicsEllipseItem::itemChange(c, v);
}

void Node::keyPressEvent(QKeyEvent *e)
{
    QGraphicsEllipseItem::keyPressEvent(e);

    int digit = 0;
    switch (e->key()) {
    case Qt::Key_0:
    case Qt::Key_1:
    case Qt::Key_2:
    case Qt::Key_3:
    case Qt::Key_4:
    case Qt::Key_5:
    case Qt::Key_6:
    case Qt::Key_7:
    case Qt::Key_8:
    case Qt::Key_9:
        digit = e->key() - Qt::Key_0;
        break;
    default:
        return;
    }

    if (_inputTimer.isActive()) {
        _number = _number * 10 + digit;
        _inputTimer.stop();
    } else {
        _number = digit;
        _inputTimer.start();
    }

    update();
}
