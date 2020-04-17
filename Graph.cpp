#include <queue>
#include "Graph.h"

template<typename T>
Graph<T>::Graph() = default;

template<typename T>
int Graph<T>::getNumEdges() const {
    return numEdges;
}

template<typename T>
int Graph<T>::getNumVertices() const {
    return numVertices;
}

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
    std::queue<T> nodes;
    std::unordered_map<T, bool> visited;
    std::unordered_map<T, T> parent;
    nodes.push(source);
    visited[source] = true;
    while (not nodes.empty()) {
        auto node = nodes.front();
        nodes.pop();
        for (const auto &vert : adjLst[node]) {  // forward edges
            if (forwardFlow[{node, vert}] <= 0)
                continue;
            if (not visited[vert]) {
                nodes.push(vert);
                parent[vert] = node;
                visited[vert] = true;
            }
            if (vert == target) {
                return backtrackPath(vert, source, parent);
            }
        }
        for (const auto &vert : backAdjLst[node]) {  // backward edges
            if (backwardFlow[{node, vert}] <= 0)
                continue;
            if (not visited[vert]) {
                nodes.push(vert);
                parent[vert] = node;
                visited[vert] = true;
            }
            if (vert == target) {
                return backtrackPath(vert, source, parent);
            }
        }
    }
    return {};
}

template<typename T>
void Graph<T>::augment(EdgeMap<T> &flow, std::vector<Edge<T>> path) {
    // find bottleneck
    unsigned int minFlow = std::numeric_limits<unsigned int>::max();
    for (const auto &edge : path) {
        minFlow = std::min(minFlow, forwardFlow[edge]);
    }

    // augment flow
    for (const auto &edge : path) {
        if (adjLst[edge.u].contains(edge.v)) {  // forward edge
            flow[edge] += minFlow;
            forwardFlow[edge] -= minFlow;
            backwardFlow[edge] += minFlow;
        } else {  // backward edge
            flow[edge] -= minFlow;
            forwardFlow[edge] += minFlow;
            backwardFlow[edge] -= minFlow;
        }
    }
}

template<typename T>
EdgeMap<T> Graph<T>::maxFlow(const T &source, const T &target) {
    forwardFlow = edgeCapacities;
    EdgeMap<T> flow;
    auto path = getPath(source, target);
    while (not path.empty()) {
        augment(flow, path);
        path = getPath(source, target);
    }
    return flow;
}

template<typename T>
std::unordered_map<T, bool> Graph<T>::minCut(T source) {
    std::queue<T> nodes;
    std::unordered_map<T, bool> visited;
    nodes.push(source);
    visited[source] = true;
    while (not nodes.empty()) {
        auto node = nodes.front();
        nodes.pop();
        for (const auto &vert : adjLst[node]) {  // forward edges
            if (forwardFlow[{node, vert}] <= 0)
                continue;
            if (not visited[vert]) {
                nodes.push(vert);
                visited[vert] = true;
            }
            
        }
        for (const auto &vert : backAdjLst[node]) {  // backward edges
            if (backwardFlow[{node, vert}] <= 0)
                continue;
            if (not visited[vert]) {
                nodes.push(vert);
                visited[vert] = true;
            }
        }
    }
    return visited;
}

template<typename T>
const EdgeMap<T> &Graph<T>::getEdgeCapacities() const {
    return edgeCapacities;
}

template
class Graph<int>;
