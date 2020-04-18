#ifndef UTILS_H
#define UTILS_H

#include "Graph.h"

/**
 * @brief Read flow graph information from file
 * @param path Path to file containing graph
 * @return Tuple of Graph (initialized as per file), source vertex and target vertex
 */
std::tuple<Graph<int>, int, int> readFlowGraph(const std::string &path);

/**
 * @brief Read bipartite graph information from file
 * @param path Path to file containing bipartite graph
 * @return Tuple of Graph (initialized as per file), source vertex and target vertex
 */
std::tuple<Graph<int>, int, int, int> readBipartiteGraph(const std::string &path);

#endif //UTILS_H
