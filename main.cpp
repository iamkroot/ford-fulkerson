#include <iostream>
#include "Graph.h"

int main() {
    Graph<int> graph;
    graph.addEdge(0, 1, 20);
    graph.addEdge(0, 2, 10);
    graph.addEdge(1, 2, 30);
    graph.addEdge(1, 3, 10);
    graph.addEdge(2, 3, 20);
    return 0;
}
