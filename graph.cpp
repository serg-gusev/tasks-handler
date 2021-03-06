#include "graph.h"

void GraphNode::addParent(int parentIndex)
{
    if (!parentIndexes.contains(parentIndex)) {
        parentIndexes.append(parentIndex);
    }
}

void GraphNode::removeParent(int parentIndex)
{
    if (parentIndexes.contains(parentIndex)) {
        parentIndexes.removeAll(parentIndex);
    }
}

Graph::Graph()
{

}

bool Graph::isEmpty() const
{
    return _nodes.isEmpty();
}

void Graph::addNode(const GraphNode &node)
{
    if (!_nodes.contains(node)) {
        _nodes.append(node);
    }
}

void Graph::removeNode(const GraphNode &node)
{
    if (_nodes.contains(node)) {
        _nodes.removeAll(node);
    }
}

GraphNode Graph::find(int index) const
{
    for (auto graphNode : _nodes) {
        if (graphNode.index == index)
            return graphNode;
    }

    return GraphNode();
}

QList<GraphNode> Graph::nodes() const
{
    return _nodes;
}

int Graph::taskStartTime(const GraphNode &node, int &parentsCount) const
{
    int result = 0;
    for (auto parentIndex : node.parentIndexes) {
        auto parentNode = find(parentIndex);
        int tempParentsCount = 0;
        int parentStartTime = taskStartTime(parentNode, tempParentsCount);
        if (parentNode.weight + parentStartTime > result) {
            result = parentNode.weight + parentStartTime;
            parentsCount = tempParentsCount + 1;
        }
    }
    return result;
}

QList<GraphNode> Graph::tasksForTime(int time) const
{
    QList<GraphNode> res;

    int tmp;
    for (auto graphNode : _nodes) {
        auto nodeStartTime = taskStartTime(graphNode, tmp);
        if (nodeStartTime <= time && time < nodeStartTime + graphNode.weight) {
            res << graphNode;
        }
    }

    return res;
}

GraphNode &Graph::operator [](int nodeIndex)
{
    for (int i = 0; i < _nodes.count(); i++) {
        if (_nodes[i].index == nodeIndex)
            return _nodes[i];
    }

    return _nodes[0];
}
