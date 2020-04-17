cmake_minimum_required(VERSION 3.17)
project(ford_fulkerson)

set(CMAKE_CXX_STANDARD 20)

add_executable(ford_fulkerson main.cpp Graph.cpp Graph.h Stopwatch.hpp Utils.cpp Utils.h)