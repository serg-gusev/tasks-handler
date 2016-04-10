#include "graph.h"

void GraphNode::addChild(GraphNode *child)
{
    if (!childs.contains(child)) {
        childs.append(child);
    }
}

void GraphNode::removeChild(GraphNode *child)
{
    if (childs.contains(child)) {
        childs.removeAll(child);
    }
}

void GraphNode::addParent(GraphNode *parent)
{
    if (!parents.contains(parent)) {
        parents.append(parent);
    }
}

void GraphNode::removeParent(GraphNode *parent)
{
    if (parents.contains(parent)) {
        parents.removeAll(parent);
    }
}

Graph::Graph(GraphNode *rootNode) :
    _root(rootNode)
{

}

bool Graph::isEmpty() const
{
    return _nodes.isEmpty();
}

void Graph::addNode(GraphNode *node)
{
    if (!contains(node)) {
        _nodes.append(node);
    }
}

void Graph::removeNode(GraphNode *node)
{
    if (contains(node)) {
        _nodes.removeAll(node);
    }
}

bool Graph::contains(GraphNode *node) const
{
    return find(node->index);
}

GraphNode *Graph::find(int index) const
{
    for (auto graphNode : _nodes) {
        if (graphNode && graphNode->index == index)
            return graphNode;
    }

    return nullptr;
}

QList<GraphNode *> Graph::nodes() const
{
    return _nodes;
}
