#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Graph.h"
#include "BipartiteMatching.h"

void findMaxFlow(const std::string &path) {
    std::ifstream input(path);
    Graph<int> graph;
    int E{}, source{}, target{};
    input >> E >> source >> target;
    int u{}, v{}, capacity{};
    for (int i = 0; i < E; i++) {
        input >> u >> v >> capacity;
        graph.addEdge(u, v, capacity);
    }
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
}

int main(int argc, char *argv[]) {
    std::stringstream help;
    help << "Usage:" << std::endl
         << "ford_fulkerson [maxflow|maxmatch] DATASET_PATH [DATASET_PATH...]" << std::endl
         << std::endl
         << "maxflow - \t For each graph, find the maximum flow from source to sink and print the flow in each edge to stdout" << std::endl
         << "maxmatch -\t For each bipartite graph, find the maximum matching and print the matching to stdout" << std::endl
         << std::endl
         << "DATASET_PATH" << std::endl
         << "\tFor maxflow:\tThe DATASET_PATH should be a path (no spaces) to a file containing details of the directed graph."
         << std::endl
         << "\t\t\tThe first line of the file should have: numberOfEdges sourceVert sinkVert"
         << std::endl
         << "\t\t\tThe following numberOfEdges lines should have the edges from A to B in the form: fromVert toVert"
         << std::endl
         << "\t\t\twhere 0 <= fromVert <= V and 0 <= toVert <= V, where V is the total number of vertices in the graph"
         << std::endl
         << std::endl
         << "\tFor maxmatch:\tThe DATASET_PATH should be a path (no spaces) to a file containing details of the bipartite graph."
         << std::endl
         << "\t\t\tThe first line of the file should have: numberOfEdges numberOfVerticesInA numberOfVerticesInB"
         << std::endl
         << "\t\t\tThe following numberOfEdges lines should have the edges from A to B in the form: vertInA vertInB"
         << std::endl
         << "\t\t\twhere 1 <= vertInA <= numberOfVerticesInA and 1 <= vertInB <= numberOfVerticesInB"
         << std::endl;
         
    if (argc < 2) {
        std::cout << help.str();
        return 0;
    }
    std::string op = argv[1];
    if (op != "maxmatch" && op != "maxflow") {
        std::cerr << help.str();
        return -1;
    }
    for (int i = 2; i < argc; ++i) {
        if (op == "maxflow") {
            findMaxFlow(argv[i]);
        } else if (op == "maxmatch") {
            maxBipartiteMatching(argv[i]);
        }
    }
}

