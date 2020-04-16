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

	// -------------------------START OF INPUT-------------------------
	
	int E{}, A{}, B{};
	std::cout << "Enter number of edges, vertices in A, vertices in B:\n";
	std::cin >> E >> A >> B;
	int u{}, v{};
    int source = 0, target = A+B+1;
	std::cout << "Enter " << E << " edges from A to B (1-indexed) :\n";
	for (int i = 0; i < E; i++)
	{
		std::cin >> u >> v;
		graph.addEdge(source, u, 1);
		graph.addEdge(u, A+v, 1);
		graph.addEdge(A+v, target, 1);
	}

	// -------------------------END OF INPUT-------------------------
	
    auto flow = graph.maxFlow(source, target);
    unsigned int flowVal = 0;
    std::cout << "(A -> B)" <<std::endl;
    for (const auto &item : flow) {
		if (item.first.u != source && item.first.v != target) {
	        std::cout << "(" << item.first.u << " -> " << (item.first.v - A) << ")" << std::endl;
		}
		if (item.first.u == source)
            flowVal += item.second;
    }

    if (checkFlow(flow, graph.getEdgeCapacities())) {
        std::cout << "Matching: " << flowVal << std::endl;
    } else {
        std::cout << "Invalid flow" << std::endl;
    }
    return 0;
}
