#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Graph.h"
#include "Utils.h"

void maxBipartiteMatching(const std::string &path) {
    std::ifstream input(path);
    Graph<int> graph;
    int E{}, A{}, B{};
    input >> E >> A >> B;
    int u{}, v{};
    int source = 0, target = A + B + 1;
    for (int i = 0; i < E; i++) {
        input >> u >> v;
        graph.addEdge(source, u, 1);
        graph.addEdge(u, A + v, 1);
        graph.addEdge(A + v, target, 1);
    }

    Stopwatch<> stopwatch;
    auto flow = graph.maxFlow(source, target);
    auto fordFulkersonTime = stopwatch.stop();
    unsigned int flowVal = 0;
    std::cout << "(A -> B)" << std::endl;
    for (const auto &item : flow) {
        if (item.first.u != source && item.first.v != target and item.second > 0) {
            std::cout << "(" << item.first.u << " -> " << (item.first.v - A) << ")" << std::endl;
        }
        if (item.first.u == source)
            flowVal += item.second;
    }

    if (checkFlow(flow, graph.getEdgeCapacities())) {
        std::cout << "Matchings: " << flowVal << std::endl << "Time: " << fordFulkersonTime << "μs." << std::endl;
    } else {
        std::cout << "Invalid flow" << std::endl;
    }
}

int main(int argc, char* argv[]) {
    std::stringstream help;
    help << "Usage:" << std::endl
         << "bipartite_matching DATASET_PATH [DATASET_PATH...]" << std::endl
         << std::endl
         << "The DATASET_PATH should be a path (no spaces) to a file containing details of the bipartite graph."
         << std::endl
         << "The first line of the file should have: numberOfEdges numberOfVerticesInA numberOfVerticesInB"
         << std::endl
         << "The following numberOfEdges lines should have the edges from A to B in the form: vertInA vertInB"
         << ", where 1 <= vertInA <= numberOfVerticesInA and 1 <= vertInB <= numberOfVerticesInB"
         << std::endl;
    if (argc < 2) {
        std::cout << help.str();
        return 0;
    }
    for (int i = 1; i < argc; ++i) {
        maxBipartiteMatching(argv[i]);
    }
    return 0;
}
