#include "node.h"

#include <QPen>
#include <QPainter>
#include <QFont>
#include <QCursor>
#include <QGraphicsSceneMouseEvent>

Node::Node() :
    QGraphicsEllipseItem(0, 0, 30, 30)
{
    setPen(QPen(Qt::red, 3));
}

void Node::paint(QPainter *p, const QStyleOptionGraphicsItem *o, QWidget *w)
{
    QGraphicsEllipseItem::paint(p, o, w);

    auto f = p->font();
    f.setPixelSize(16);
    p->setFont(f);
    p->setPen(Qt::black);
    p->drawText(boundingRect(), Qt::AlignCenter, QString::number(_number));
}

void Node::mousePressEvent(QGraphicsSceneMouseEvent *e)
{
    setCursor(Qt::ClosedHandCursor);
}

void Node::mouseMoveEvent(QGraphicsSceneMouseEvent *e)
{

}

void Node::mouseReleaseEvent(QGraphicsSceneMouseEvent *e)
{
    setCursor(Qt::OpenHandCursor);
}

