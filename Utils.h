#ifndef UTILS_H
#define UTILS_H

#include "Graph.h"

std::tuple<Graph<int>, int, int> readFlowGraph(const std::string &path);

std::tuple<Graph<int>, int, int, int> readBipartiteGraph(const std::string &path);

#endif //UTILS_H
