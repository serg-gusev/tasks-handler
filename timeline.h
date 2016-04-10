#ifndef TIMELINE_H
#define TIMELINE_H

#include <QGraphicsView>
#include <QGraphicsRectItem>

#include "graph.h"

class TimelineTask : public QGraphicsRectItem
{
public:
    TimelineTask(GraphNode *graphNode);

    void paint(QPainter *p, const QStyleOptionGraphicsItem *o, QWidget *w = nullptr) override;

    static const int taskHeight = 50;
    static const int taskSingleWidth = 40;

    int index() const { return _node->index; }

private:
    GraphNode *_node = nullptr;
    QColor _color;
};

class Timeline : public QGraphicsView
{
public:
    Timeline(Graph *graph, QWidget *parent = nullptr);

    void drawTask(GraphNode *graphNode);
    void drawGraph(Graph *graph);

private:
    int findLongestWay(GraphNode *node, int &parentsCount);

    QGraphicsScene *_scene = nullptr;
};

#endif // TIMELINE_H
