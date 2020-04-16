#include <iostream>
#include "Graph.h"

template<typename T>
bool checkFlow(const EdgeMap<T> &flow, const EdgeMap<T> &capacity) {
    std::unordered_map<T, unsigned int> out, in;
    for (const auto &edgeFlow : flow) {
        if (edgeFlow.second < 0 or edgeFlow.second > capacity.at(edgeFlow.first)) {
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

    std::unordered_map<int, bool> visited;

    visited = graph.minCut(source);
    int edges = graph.getNumEdges();
    EdgeMap<int> edgeCapaticies = graph.getEdgeCapacities();

    std::cout<<"\nThe min-cut edges are as follows: \n";
    for(auto item : edgeCapaticies){
        if(visited[item.first.u] && !visited[item.first.v]){
            std::cout<<item.first.u<<" - "<<item.first.v<<"\n";
        }
    }
    return 0;
}
