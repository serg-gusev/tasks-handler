#ifndef NODE_H
#define NODE_H

#include <QGraphicsEllipseItem>
#include <QTimer>

class Node : public QGraphicsEllipseItem
{
public:
    Node();

    void paint(QPainter *p, const QStyleOptionGraphicsItem *o, QWidget *w = nullptr) override;

    void setInteractable(bool interactable);

protected:
    void keyPressEvent(QKeyEvent *e) override;

private:
    int _number = 1;
    QTimer _inputTimer;
};

#endif // NODE_H
