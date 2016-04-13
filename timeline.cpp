#include "timeline.h"
#include "ui_timeline.h"

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

Timeline::Timeline(const Graph &graph, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Timeline)
{
    ui->setupUi(this);

    _scene = new QGraphicsScene(0, 0, 800, 600, this);
    ui->timelineView->setScene(_scene);

    _graphs << graph;
    auto g = graph;
    handleGraph(g);

    drawGraph(0);
}

Timeline::~Timeline()
{
    delete ui;
}

void Timeline::drawTask(const GraphNode &graphNode, const Graph &graph)
{
    auto task = new TimelineTask(graphNode);

    int parentsCount = 0;
    int taskStartTime = graph.taskStartTime(graphNode, parentsCount);
    int xOffset = taskStartTime * TimelineTask::taskSingleWidth + 100;
    int yOffset = 500 - TimelineTask::taskHeight;

    for (int i = 0; i < _scene->items().count(); i++) {
        for (auto item : _scene->items()) {
            auto taskBoundingRect = task->boundingRect();
            auto taskRect = QRectF(xOffset + 2, yOffset + 2, taskBoundingRect.width() - 2, taskBoundingRect.height() - 2);

            auto itemTask = dynamic_cast<TimelineTask *>(item);
            if (itemTask) {
                auto itemBoundingRect = itemTask->boundingRect();
                auto itemRect = QRectF(itemTask->x() + 2, itemTask->y() + 2, itemBoundingRect.width() - 2, itemBoundingRect.height() - 2);

                if (itemRect.intersects(taskRect)) {
                    yOffset -= TimelineTask::taskHeight;
                    break;
                }
            }
        }
    }

    task->moveBy(xOffset, yOffset);
    _scene->addItem(task);
}

void Timeline::drawGraph(int graphIndex)
{
    if (graphIndex == _currentGraphIndex)
        return;

    _currentGraphIndex = graphIndex;
    ui->previousButton->setEnabled(graphIndex > 0);
    ui->nextButton->setEnabled(graphIndex < _graphs.count() - 1);

    _scene->clear();

    _scene->addLine(100, 100, 100, 500);
    _scene->addLine(100, 500, 700, 500);

    auto graph = _graphs[graphIndex];
    for (auto node : graph.nodes()) {
        drawTask(node, graph);
    }
}

void Timeline::handleGraph(Graph &graph)
{
    for (int i = 0; graph.tasksForTime(i).count() > 0; i++) {
        auto tasks = graph.tasksForTime(i);
        if (tasks.count() > 2) {
            for (auto task1 : tasks) {
                for (auto task2 : tasks) {
                    if (task1 == task2)
                        continue;

                    graph[task2.index].addParent(task1.index);

                    _graphs << graph;
                    handleGraph(graph);

                    graph[task2.index].removeParent(task1.index);
                }
            }
        }
    }
}

void Timeline::on_previousButton_clicked()
{
    drawGraph(_currentGraphIndex - 1);
}

void Timeline::on_nextButton_clicked()
{
    drawGraph(_currentGraphIndex + 1);
}

void Timeline::on_optimalButton_clicked()
{
    int minTime = INT_MAX, minTimeIndex = 0;
    for (int i = 0; i < _graphs.count(); i++) {
        auto graph = _graphs[i];
        int time = 0, tasksCount;
        do {
            tasksCount = graph.tasksForTime(time).count();
            time++;
        } while (0 < tasksCount && tasksCount <= 2);

        if (graph.tasksForTime(time - 1).count() > 0)
            continue;

        if (time < minTime) {
            minTime = time;
            minTimeIndex = i;
        }
    }

    drawGraph(minTimeIndex);
}
