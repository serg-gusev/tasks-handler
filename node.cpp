#include "node.h"

#include <QPen>
#include <QPainter>
#include <QFont>
#include <QKeyEvent>

Node::Node() :
    QGraphicsEllipseItem(0, 0, 30, 30)
{
    setPen(QPen(Qt::red, 3));
    setFlags(ItemIsMovable | ItemIsFocusable | ItemIsSelectable);
    setSelected(true);

    _inputTimer.setInterval(1500);
    _inputTimer.setSingleShot(true);
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

