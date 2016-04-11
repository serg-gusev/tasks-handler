#ifndef TIMELINE_H
#define TIMELINE_H

#include <QGraphicsView>
#include <QGraphicsRectItem>

#include "graph.h"

class TimelineTask : public QGraphicsRectItem
{
public:
    TimelineTask(const GraphNode &graphNode);

    void paint(QPainter *p, const QStyleOptionGraphicsItem *o, QWidget *w = nullptr) override;

    static const int taskHeight = 50;
    static const int taskSingleWidth = 40;

    int index() const { return _node.index; }

private:
    GraphNode _node;
    QColor _color;
};

class Timeline : public QGraphicsView
{
public:
    Timeline(Graph *graph, QWidget *parent = nullptr);

    void drawTask(const GraphNode &graphNode, Graph *graph);
    void drawGraph(Graph *graph);

private:
    QGraphicsScene *_scene = nullptr;
};

#endif // TIMELINE_H
