#ifndef GRAPH_H
#define GRAPH_H

#include <QList>

struct GraphNode
{
    void addChild(GraphNode *child);
    void removeChild(GraphNode *child);
    QList<GraphNode *> childs;

    void addParent(GraphNode *parent);
    void removeParent(GraphNode *parent);
    QList<GraphNode *> parents;

    int index = 0;
    int weight = 0;
};

class Graph
{
public:
    Graph(GraphNode *rootNode = nullptr);
    bool isEmpty() const;

    void addNode(GraphNode *node);
    void removeNode(GraphNode *node);
    bool contains(GraphNode *node) const;
    bool contains(int index) const;
    GraphNode *find(int index) const;
    QList<GraphNode *> nodes() const;

private:
    GraphNode *_root;
    QList<GraphNode *> _nodes;
};

#endif // GRAPH_H
