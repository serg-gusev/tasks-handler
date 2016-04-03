#include "node.h"

#include <QPen>

Node::Node() :
    QGraphicsEllipseItem(0, 0, 30, 30)
{
    setPen(QPen(Qt::red));
    setBrush(QBrush(Qt::blue));
}

//QRectF Node::boundingRect() const
//{
//    return QRectF(0, 0, 30, 30);
//}


