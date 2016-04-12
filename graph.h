#ifndef GRAPH_H
#define GRAPH_H

#include <QList>

struct GraphNode
{
    void addChild(int childIndex);
    void removeChild(int childIndex);
    QList<int> childsIndexes;

    void addParent(int parentIndex);
    void removeParent(int parentIndex);
    QList<int> parentIndexes;

    bool operator ==(const GraphNode &other)
    {
        return index == other.index;
    }

    int index = 0;
    int weight = 0;
};

class Graph
{
public:
    Graph();
    bool isEmpty() const;

    void addNode(const GraphNode &node);
    void removeNode(const GraphNode &node);
    bool contains(const GraphNode &node) const;
    bool contains(int index) const;
    GraphNode find(int index) const;
    QList<GraphNode> nodes() const;

    int taskStartTime(const GraphNode &node, int &parentsCount) const;

    QList<GraphNode> tasksForTime(int time) const;
    int tasksTime() const;

    GraphNode &operator [](int nodeIndex);

private:
    QList<GraphNode> _nodes;
};

#endif // GRAPH_H
