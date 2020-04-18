#ifndef GRAPH_H
#define GRAPH_H

#include <unordered_set>
#include <unordered_map>
#include <vector>

/**
 * @struct Edge
 * @brief Representation of a directed edge
 */
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

/**
 * @struct EdgeHash
 * @brief Hash Generator for Edge
 */
template<typename T>
struct EdgeHash {

    /**
     * @brief () operator overriding
     * @return Hash of given edge
     */
    inline std::size_t operator()(const Edge<T> &edge) const {
        return std::hash<T>{}(edge.u) / 2 + std::hash<T>{}(edge.v) / 2;
    }
};

template<typename T>
using AdjLst = std::unordered_map<T, std::unordered_set<T>>;

template<typename T>
using EdgeMap = std::unordered_map<Edge<T>, unsigned int, EdgeHash<T>>;

/**
 * @class Graph
 * @brief Get the maxFlow and minCut by repeatedly finding augmenting paths through the residual graphs
 */
template<typename T>
class Graph {
    int numEdges{0};
    int numVertices{0};
    AdjLst<T> adjLst;
    AdjLst<T> backAdjLst;
    EdgeMap<T> edgeCapacities;
    EdgeMap<T> flow;

public:
    /**
     * @brief Initialize an empty graph
     */
    Graph();

    /**
     * @brief Get edge capacities of the graph
     * @return Edge capacities
     */
    const EdgeMap<T> &getEdgeCapacities() const;

    /**
     * @brief Add a vertex to the graph
     * @param v Vertex to be added
     */
    void addVertex(T v);

    /**
     * @brief Add an edge to the graph
     * @param u Vertex from which the edge originates 
     * @param v Vertex on which the edge terminates
     * @param capacity Edge Capacity 
     */
    void addEdge(T u, T v, unsigned int capacity);

    /**
     * @brief Get a path from source to target
     * @param source Source Vertex
     * @param target Target Vertex 
     * @return Path from source to target
     */
    std::vector<Edge<T>> getPath(T source, T target);

    /**
     * @brief Augment the chosen path
     * @param path Path to be augmented
     * @return Augmented path
     */
    void augment(std::vector<Edge<T>> path);

    /**
     * @brief Get the maximum flow value possible from source to target
     * @param source Source Vertex
     * @param target Target Vertex
     * @return Maximum flow value
     */
    EdgeMap<T> maxFlow(const T &source, const T &target);

    /**
     * @brief Get the minimum st-cut
     * @param source Source Vertex
     * @param target Target Vertex
     * @return Minimum st-cut value
     */
    std::pair<std::unordered_set<T>, std::unordered_set<T>> minCut(const T &source, const T &target);
};

/**
     * @brief Check if flow is valid
     * @param flow The flow value of the edge
     * @param edgeCapacities The respective edge capacity values
     * @return True if flow is valid else False
     */
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
