#include "graph.h"

Graph::Graph(GraphNode *rootNode) :
    _root(rootNode)
{

}

bool Graph::isValid() const
{
    return _root;
}

