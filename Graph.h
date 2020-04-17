#ifndef GRAPH_H
#define GRAPH_H

#include <unordered_set>
#include <unordered_map>
#include <vector>

template<typename T>
struct Edge {
    T u{};
    T v{};

    Edge(T u, T v) : u(u), v(v) {}

    bool operator==(const Edge &rhs) const {
        return u == rhs.u && v == rhs.v;
    }

    Edge<T> reverse() const {
        return {v, u};
    }
};

template<typename T>
struct EdgeHash {
    inline std::size_t operator()(const Edge<T> &edge) const {
        return std::hash<T>{}(edge.u) / 2 + std::hash<T>{}(edge.v) / 2;
    }
};

template<typename T>
using AdjLst = std::unordered_map<T, std::unordered_set<T>>;

template<typename T>
using EdgeMap = std::unordered_map<Edge<T>, unsigned int, EdgeHash<T>>;

template<typename T>
class Graph {
    int numEdges{0};
    int numVertices{0};
    AdjLst<T> adjLst;
    AdjLst<T> backAdjLst;
    EdgeMap<T> edgeCapacities;
    EdgeMap<T> flow;

public:

    Graph();

    const EdgeMap<T> &getEdgeCapacities() const;

    void addVertex(T v);

    void addEdge(T u, T v, unsigned int capacity);

    std::vector<Edge<T>> getPath(T source, T target);

    void augment(std::vector<Edge<T>> path);

    EdgeMap<T> maxFlow(const T &source, const T &target);

    std::pair<std::unordered_set<T>, std::unordered_set<T>> minCut(const T &source, const T &target);
};

template<typename T>
bool checkFlow(const EdgeMap<T> &flow, const EdgeMap<T> &edgeCapacities) {
    std::unordered_map<T, unsigned int> out, in;
    for (const auto &edgeFlow : flow) {
        if (edgeFlow.second < 0 or edgeFlow.second > edgeCapacities.at(edgeFlow.first)) {
            return false;
        }
        out[edgeFlow.first.u] += edgeFlow.second;
        in[edgeFlow.first.v] += edgeFlow.second;
    }
    for (const auto &item : out) {
        if (not in.contains(item.first))
            return item.second != 0;
        if (item.second != in[item.first])
            return false;
    }
    return true;
}

#endif //GRAPH_H
