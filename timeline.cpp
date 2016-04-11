#include "timeline.h"

#include <QPen>
#include <QPainter>
#include <QDebug>

TimelineTask::TimelineTask(const GraphNode &graphNode) :
    QGraphicsRectItem(0, 0, graphNode.weight * taskSingleWidth, taskHeight),
    _node(graphNode)
{
    _color = Qt::black;
    setPen(QPen(_color));
}

void TimelineTask::paint(QPainter *p, const QStyleOptionGraphicsItem *o, QWidget *w)
{
    QGraphicsRectItem::paint(p, o, w);

    p->drawText(boundingRect(), Qt::AlignCenter, QString::number(_node.index));
}

Timeline::Timeline(Graph *graph, QWidget *parent) :
    QGraphicsView(parent)
{
    _scene = new QGraphicsScene(0, 0, 800, 600, this);
    setScene(_scene);

    drawGraph(graph);
}

void Timeline::drawTask(const GraphNode &graphNode, Graph *graph)
{
    auto task = new TimelineTask(graphNode);

    int parentsCount = 0;
    int taskStartTime = graph->taskStartTime(graphNode);
    int xOffset = taskStartTime * TimelineTask::taskSingleWidth + 100 + parentsCount * 2;
    int yOffset = 500 - TimelineTask::taskHeight - 2;

    for (int i = 0; i < _scene->items().count(); i++) {
        for (auto item : _scene->items()) {
            auto taskRect = QRectF(QPointF(xOffset, yOffset), task->boundingRect().size());

            auto itemTask = dynamic_cast<TimelineTask *>(item);
            if (itemTask) {
                auto itemRect = QRectF(itemTask->pos(), itemTask->boundingRect().size());
                if (itemRect.intersects(taskRect)) {
                    yOffset -= TimelineTask::taskHeight + 2;
                    break;
                }
            }
        }
    }

    task->moveBy(xOffset, yOffset);
    _scene->addItem(task);
}

void Timeline::drawGraph(Graph *graph)
{
    _scene->clear();

    _scene->addLine(100, 100, 100, 500);
    _scene->addLine(100, 500, 700, 500);

    for (auto node : graph->nodes()) {
        drawTask(node, graph);
    }
}
