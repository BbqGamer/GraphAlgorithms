#ifndef EDGELIST_H
#define EDGELIST_H

#include <stdexcept>
#include "Graph.h"
#include <iostream>
#include <vector>

class EdgeList : public Graph {

    std::vector<int> vList;
    std::vector<std::pair<int, int>> eList;

public:
    EdgeList() {};
    EdgeList(std::vector<int> vertexList, std::vector<std::pair<int, int>> edgeList) {
        initialize(vertexList, edgeList);
    };

    bool areNeighbors(int v, int w);
    int getNumVertices();
    void initialize(std::vector<int> vertexList, std::vector<std::pair<int, int>> edgeList, bool directed = 0);
};

#endif