#include <queue>
#include "Graph.h"

template<typename T>
Graph<T>::Graph() = default;

template<typename T>
void Graph<T>::addVertex(T v) {
    if (not adjLst.contains(v)) {
        adjLst[v] = {};
        numVertices++;
    }
}

template<typename T>
void Graph<T>::addEdge(T u, T v, unsigned int capacity) {
    addVertex(u);
    addVertex(v);
    adjLst[u].insert(v);
    backAdjLst[v].insert(u);
    edgeCapacities[{u, v}] = capacity;
    numEdges++;
}

template<typename T>
std::vector<Edge<T>> backtrackPath(T vert, const T &source, std::unordered_map<T, T> &parent) {
    std::vector<Edge<T>> path;
    do {
        path.emplace_back(parent[vert], vert);
        vert = parent[vert];
    } while (vert != source);
    std::reverse(path.begin(), path.end());
    return path;
}

template<typename T>
std::vector<Edge<T>> Graph<T>::getPath(T source, T target) {
    if (source == target)
        return {};
    std::queue<T> nodes;
    std::unordered_map<T, bool> visited;
    std::unordered_map<T, T> parent;
    nodes.push(source);
    visited[source] = true;
    while (not nodes.empty()) {
        auto node = nodes.front();
        nodes.pop();
        if (node == target) {
            return backtrackPath(node, source, parent);
        }
        for (const auto &vert : adjLst[node]) {  // forward edges
            Edge edge = {node, vert};
            if (edgeCapacities[edge] > flow[edge] and not visited[vert]) {
                nodes.push(vert);
                parent[vert] = node;
                visited[vert] = true;
            }
        }
        for (const auto &vert : backAdjLst[node]) {  // backward edges
            if (flow[{vert, node}] > 0 and not visited[vert]) {
                nodes.push(vert);
                parent[vert] = node;
                visited[vert] = true;
            }
        }
    }
    return {};
}

template<typename T>
void Graph<T>::augment(std::vector<Edge<T>> path) {
    // find bottleneck
    unsigned int minFlow = std::numeric_limits<unsigned int>::max();
    for (const auto &edge : path) {
        if (edgeCapacities.contains(edge))  // forward edge
            minFlow = std::min(minFlow, edgeCapacities[edge] - flow[edge]);
        else  // backward edge
            minFlow = std::min(minFlow, flow[edge.reverse()]);
    }

    // augment flow
    for (const auto &edge : path) {
        if (edgeCapacities.contains(edge)) {  // forward edge
            flow[edge] += minFlow;
        } else {  // backward edge
            flow[edge.reverse()] -= minFlow;
        }
    }
}

template<typename T>
EdgeMap<T> Graph<T>::maxFlow(const T &source, const T &target) {
    flow = {};
    for (const auto &edgeCapacity : edgeCapacities) {
        flow[edgeCapacity.first] = 0;  // initialize flow for each edge to be 0
    }
    auto path = getPath(source, target);
    while (not path.empty()) {
        augment(path);
        path = getPath(source, target);
    }
    return flow;
}

template<typename T>
const EdgeMap<T> &Graph<T>::getEdgeCapacities() const {
    return edgeCapacities;
}

template<typename T>
std::pair<std::unordered_set<T>, std::unordered_set<T>> Graph<T>::minCut(const T &source, const T &target) {
    std::unordered_set<T> reachable, unreachable;
    maxFlow(source, target);
    if (flow.empty())
        return {};
    std::queue<T> nodes;
    nodes.push(source);
    while (not nodes.empty()) {
        auto node = nodes.front();
        nodes.pop();
        reachable.insert(node);
        for (const auto &vert : adjLst[node]) {  // forward edges
            Edge edge = {node, vert};
            if (edgeCapacities[edge] > flow[edge] and not reachable.contains(vert)) {
                nodes.push(vert);
            }
        }
        for (const auto &vert : backAdjLst[node]) {  // backward edges
            if (flow[{vert, node}] > 0 and not reachable.contains(vert)) {
                nodes.push(vert);
            }
        }
    }
    for (const auto &item : adjLst) {
        if (not reachable.contains(item.first))
            unreachable.insert(item.first);
    }
    return {reachable, unreachable};
}

template
class Graph<int>;
