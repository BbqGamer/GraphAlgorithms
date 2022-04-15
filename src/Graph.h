#ifndef GRAPH_H
#define GRAPH_H

#include<vector>

class Graph {
public:
    virtual bool areNeighbors(int v, int w) = 0;
    virtual int getNumVertices() = 0;
    virtual void initialize(std::vector<int> vertexList, std::vector<std::pair<int, int>> edgeList) = 0;
};

#endif