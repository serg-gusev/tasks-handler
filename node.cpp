#include "node.h"

#include <QPen>

Node::Node() :
    QGraphicsEllipseItem(0, 0, 30, 30)
{
    setPen(QPen(Qt::red, 3));
}

//QRectF Node::boundingRect() const
//{
//    return QRectF(0, 0, 30, 30);
//}


