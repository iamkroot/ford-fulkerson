#ifndef GRAPH_H
#define GRAPH_H

#include <unordered_set>
#include <unordered_map>

template<typename T>
struct VertEdge {
    T v{};
    unsigned int capacity{};
public:
    VertEdge(T v, unsigned int capacity) : v(v), capacity(capacity) {}

    bool operator==(const VertEdge &rhs) const {
        return v == rhs.v && capacity == rhs.capacity;
    }
};

template<typename T>
struct vertEdgeHash {
    inline std::size_t operator()(const VertEdge<T> &vertEdge) const {
        return std::hash<T>{}(vertEdge.v);
    }
};

template<typename T>
using AdjLst = std::unordered_map<T, std::unordered_set<VertEdge<T>, vertEdgeHash<T>>>;

template<typename T>
class Graph {
    int numEdges{0};
    int numVertices{0};
    AdjLst<T> forwardAdjLst;
    AdjLst<T> backwardAdjLst;
public:
    Graph();

    [[nodiscard]] int getNumEdges() const;

    [[nodiscard]] int getNumVertices() const;

    const AdjLst<T> &getForwardAdjLst() const;

    const AdjLst<T> &getBackwardAdjLst() const;

    void addVertex(T v);

    void addEdge(T u, T v, unsigned int capacity);

};


#endif //GRAPH_H
