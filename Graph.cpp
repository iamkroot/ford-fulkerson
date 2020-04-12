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
const AdjLst<T> &Graph<T>::getForwardAdjLst() const {
    return forwardAdjLst;
}

template<typename T>
const AdjLst<T> &Graph<T>::getBackwardAdjLst() const {
    return backwardAdjLst;
}

template<typename T>
void Graph<T>::addVertex(T v) {
    if (not forwardAdjLst.contains(v)) {
        forwardAdjLst[v] = {};
        backwardAdjLst[v] = {};
        numVertices++;
    }
}

template<typename T>
void Graph<T>::addEdge(T u, T v, unsigned int capacity) {
    addVertex(u);
    addVertex(v);
    forwardAdjLst[u].insert({v, capacity});
    backwardAdjLst[v].insert({u, 0});
    numEdges++;
}

template
class Graph<int>;
