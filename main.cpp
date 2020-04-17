#include <iostream>
#include <sstream>
#include "Graph.h"
#include "Stopwatch.hpp"
#include "Utils.h"

using namespace std;

template<typename T>
void maxFlow(Graph<T> graph, T source, T target) {
    Stopwatch<> stopwatch;
    auto flow = graph.maxFlow(source, target);
    auto fordFulkersonTime = stopwatch.stop();

    unsigned int flowVal = 0;
    for (const auto &item : flow) {
        cout << "(" << item.first.u << ", " << item.first.v << ") = " << item.second << endl;
        if (item.first.u == source)
            flowVal += item.second;
    }

    if (checkFlow(flow, graph.getEdgeCapacities())) {
        cout << "Flow value: " << flowVal << endl << "Time: " << fordFulkersonTime << "μs." << endl;
    } else {
        cout << "Invalid flow" << endl;
    }
}

template<typename T>
void maxBipartiteMatching(Graph<T> graph, T source, T target, unsigned int numVertA) {
    Stopwatch<> stopwatch;
    auto flow = graph.maxFlow(source, target);
    auto fordFulkersonTime = stopwatch.stop();
    unsigned int flowVal = 0;
    cout << "(A -> B)" << endl;
    for (const auto &item : flow) {
        if (item.first.u != source and item.first.v != target and item.second > 0) {
            cout << "(" << item.first.u << " -> " << (item.first.v - numVertA) << ")" << endl;
        }
        if (item.first.u == source)
            flowVal += item.second;
    }

    if (checkFlow(flow, graph.getEdgeCapacities())) {
        cout << "Matchings: " << flowVal << endl << "Time: " << fordFulkersonTime << "μs." << endl;
    } else {
        cout << "Invalid flow" << endl;
    }
}

int main(int argc, char* argv[]) {
    stringstream help;
    help << "Usage:" << endl
         << "ford_fulkerson [maxflow|maxmatch] DATASET_PATH [DATASET_PATH...]" << endl
         << endl
         << "maxflow -\tFor each graph, find the maximum flow from source to sink and print the flow in each edge to stdout"
         << endl
         << "maxmatch -\tFor each bipartite graph, find the maximum matching and print the matching to stdout"
         << endl << endl
         << "DATASET_PATH -\tShould be a path (no spaces) to a file containing details of the directed graph." << endl
         << "\tFor maxflow:" << endl
         << "\t\t\tThe first line of the file should have: numberOfEdges sourceVert sinkVert" << endl
         << "\t\t\tThe following numberOfEdges lines should have the edges from A to B in the form: fromVert toVert"
         << endl << endl
         << "\tFor maxmatch:" << endl
         << "\t\t\tThe first line of the file should have: numberOfEdges numberOfVerticesInA numberOfVerticesInB"
         << endl
         << "\t\t\tThe following numberOfEdges lines should have the edges from A to B in the form: vertInA vertInB"
         << endl
         << "\t\t\twhere 1 <= vertInA <= numberOfVerticesInA and 1 <= vertInB <= numberOfVerticesInB"
         << endl;

    if (argc < 3) {
        cout << help.str();
        return 0;
    }
    string op = argv[1];
    if (op != "maxmatch" && op != "maxflow") {
        cerr << help.str();
        return -1;
    }
    for (int i = 2; i < argc; ++i) {
        std::cout << "Processing " << argv[i] << std::endl;
        if (op == "maxflow") {
            auto[graph, source, target] = readFlowGraph(argv[i]);
            maxFlow(graph, source, target);
        } else if (op == "maxmatch") {
            auto[graph, source, target, numVertA] = readBipartiteGraph(argv[i]);
            maxBipartiteMatching(graph, source, target, numVertA);
        }
        std::cout << std::endl;
    }
}

