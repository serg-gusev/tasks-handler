#ifndef GRAPH_H
#define GRAPH_H

#include <QList>

struct GraphNode
{
    QList<GraphNode *> childs;
    int index = 0;
    int weight = 0;
};

class Graph
{
public:
    Graph(GraphNode *rootNode = nullptr);
    bool isValid() const;

private:
    GraphNode *_root;
};

#endif // GRAPH_H
