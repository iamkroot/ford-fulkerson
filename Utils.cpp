#include <fstream>
#include <sstream>
#include "Utils.h"

using namespace std;

tuple<Graph<int>, int, int> readFlowGraph(const string &path) {
    ifstream input(path);
    Graph<int> graph;
    int numEdges, source, target;
    input >> numEdges >> source >> target;
    int u, v;
    unsigned int capacity = 0;
    for (int i = 0; i < numEdges; i++) {
        input >> u >> v >> capacity;
        graph.addEdge(u, v, capacity);
    }
    return {graph, source, target};
}

tuple<Graph<int>, int, int, int> readBipartiteGraph(const string &path) {
    ifstream input(path);
    Graph<int> graph;
    int numEdges, numVertA, numVertB{};
    input >> numEdges >> numVertA >> numVertB;
    int u, v;
    int source = 0, target = numVertA + numVertB + 1;
    for (int i = 0; i < numEdges; i++) {
        input >> u >> v;
        if (u < 1 or u > numVertA or v < 1 or v > numVertB) {
            stringstream msg("Invalid edge ");
            msg << u << " " << v;
            throw runtime_error(msg.str());
        }
        graph.addEdge(source, u, 1);
        graph.addEdge(u, numVertA + v, 1);
        graph.addEdge(numVertA + v, target, 1);
    }
    return {graph, source, target, numVertA};
}
