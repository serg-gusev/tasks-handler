#include "graph.h"

//void GraphNode::addChild(GraphNode *child)
//{
//    if (!childs.contains(child)) {
//        childs.append(child);
//    }
//}

//void GraphNode::removeChild(GraphNode *child)
//{
//    if (childs.contains(child)) {
//        childs.removeAll(child);
//    }
//}

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

int GraphNode::startTime() const
{
    return startTime(this) - weight;
}

int GraphNode::startTime(const GraphNode *node) const
{
    int result = node->weight;
    for (auto parent : node->parents) {
        int parentsLongestWay = startTime(parent);
        if (node->weight + parentsLongestWay > result) {
            result = node->weight + parentsLongestWay;
        }
    }
    return result;
}

Graph::Graph()
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

int Graph::taskStartTime(const GraphNode &node)
{
    int result = node.weight;
    for (auto parent : node.parentIndexes) {
        int parentsLongestWay = startTime(parent);
        if (node->weight + parentsLongestWay > result) {
            result = node->weight + parentsLongestWay;
        }
    }
    return result;
}

QList<GraphNode *> Graph::tasksForTime(int time) const
{
    QList<GraphNode *> res;

    for (auto graphNode : _nodes) {
        auto nodeStartTime = graphNode->startTime();
        if (nodeStartTime <= time && time < nodeStartTime + graphNode->weight) {
            res << graphNode;
        }
    }

    return res;
}

int Graph::tasksTime() const
{
    int i = 0;
    while (tasksForTime(i).count() > 0) {
        i++;
    }
    return i;
}

Graph Graph::optimalGraph(Graph *startGraph)
{
    static Graph optGraph;

    for (int i = 0; i < startGraph->nodes().count(); i++) {
        auto tasks = startGraph->tasksForTime(i);
        if (tasks.count() > 2) {
            for (auto node1 : tasks) {
                for (auto node2 : tasks) {
                    if (node1 != node2) {
                        node1->addChild(node2);
                        node2->addParent(node1);


                    }
                }
            }
        }
    }

    return optGraph;
}
