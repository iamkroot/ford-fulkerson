#include <iostream>
#include <fstream>
#include <string>
#include "Utils.h"

std::vector<std::pair<int, int>> readEdgeList(const std::string &path) {
    std::ifstream csv_file(path);
    if (not csv_file) {
        throw std::runtime_error("Error while opening CSV");
    }
    std::vector<std::pair<int, int>> edgeList;
    std::string row, first, second;
    while (getline(csv_file, row)) {
        auto ind = row.find(',');
        if (ind == -1) {
            throw std::runtime_error("Invalid edge list: missing ','");
        }
        first = std::string(row.begin(), row.begin() + ind);
        second = std::string(row.begin() + ind + 1, row.end());
        try {
            edgeList.emplace_back(std::stoi(first), std::stoi(second));
        } catch (std::invalid_argument &invalid_argument) {
            throw std::runtime_error("Invalid number in " + row);
        }
    }
    return edgeList;
}
