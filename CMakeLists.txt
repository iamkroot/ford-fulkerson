cmake_minimum_required(VERSION 3.17)
project(ford_fulkerson)

set(CMAKE_CXX_STANDARD 20)

add_executable(ford_fulkerson main.cpp Graph.cpp Graph.h)
add_executable(bipartite_matching BipartiteMatching.cpp Graph.cpp Graph.h Utils.cpp Utils.h)