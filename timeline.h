#ifndef TIMELINE_H
#define TIMELINE_H

#include <QWidget>
#include <QGraphicsRectItem>

#include "graph.h"

namespace Ui {
class Timeline;
}

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

class Timeline : public QWidget
{
    Q_OBJECT

public:
    Timeline(const Graph &graph, QWidget *parent = nullptr);
    ~Timeline();

    void drawTask(const GraphNode &graphNode, const Graph &graph);
    void drawGraph(int graphIndex);

    void handleGraph(Graph &graph);

private slots:
    void on_previousButton_clicked();
    void on_nextButton_clicked();
    void on_optimalButton_clicked();

private:
    Ui::Timeline *ui;

    QGraphicsScene *_scene = nullptr;
    QList<Graph> _graphs;
    int _currentGraphIndex = -1;
};

#endif // TIMELINE_H
