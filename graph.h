#ifndef GRAPH_H
#define GRAPH_H

#include <QList>

struct GraphNode
{
//    void addChild(GraphNode *child);
//    void removeChild(GraphNode *child);
//    QList<GraphNode *> childs;

    void addParent(int parentIndex);
    void removeParent(int parentIndex);
    QList<GraphNode *> parentIndexes;

    int startTime() const;
    int startTime(const GraphNode *node) const;

    int index = 0;
    int weight = 0;
};

class Graph
{
public:
    Graph();
    bool isEmpty() const;

    void addNode(GraphNode *node);
    void removeNode(GraphNode *node);
    bool contains(GraphNode *node) const;
    bool contains(int index) const;
    GraphNode *find(int index) const;
    QList<GraphNode *> nodes() const;

    int taskStartTime(const GraphNode &node);

    QList<GraphNode *> tasksForTime(int time) const;
    int tasksTime() const;

    static Graph optimalGraph(Graph *startGraph);

private:
    GraphNode *_root;
    QList<GraphNode *> _nodes;
};

#endif // GRAPH_H
