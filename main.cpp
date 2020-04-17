#include <iostream>
#include "Graph.h"

int main() {
    Graph<int> graph;
    graph.addEdge(0, 1, 10);
    graph.addEdge(0, 2, 9);
    graph.addEdge(1, 2, 2);
    graph.addEdge(1, 3, 4);
    graph.addEdge(1, 4, 8);
    graph.addEdge(2, 4, 100);
    graph.addEdge(4, 3, 6);
    graph.addEdge(3, 5, 10);
    graph.addEdge(4, 5, 10);
    int source = 0, target = 5;
    auto flow = graph.maxFlow(source, target);
    unsigned int flowVal = 0;
    for (const auto &item : flow) {
        std::cout << "(" << item.first.u << ", " << item.first.v << ") = " << item.second << std::endl;
        if (item.first.u == source)
            flowVal += item.second;
    }

    if (checkFlow(flow, graph.getEdgeCapacities())) {
        std::cout << "Flow value: " << flowVal << std::endl;
    } else {
        std::cout << "Invalid flow" << std::endl;
    }
    return 0;
}
