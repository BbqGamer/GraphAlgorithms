#ifndef EDGELIST_H
#define EDGELIST_H

#include <stdexcept>
#include "Graph.h"
#include <iostream>
#include <vector>

class EdgeList : public GraphInterface {

    std::vector<int> vertexList;
    std::vector<std::pair<int, int>> edgeList;

public:
    EdgeList() {};
    EdgeList(Graph g, bool directed = 0) {
        initialize(g, directed);
    };

    bool areNeighbors(int v, int w);
    int getNumVertices();
    void initialize(Graph g, bool directed = 0);
    bool operator==(const EdgeList &g) const;
};

#endif