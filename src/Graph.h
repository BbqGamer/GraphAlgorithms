#ifndef GRAPH_H
#define GRAPH_H

#include<vector>

typedef struct Graphtag {
    std::vector<int> vertexList;
    std::vector<std::pair<int, int>> edgeList;
} Graph;

class GraphInterface {
public:
    virtual bool areNeighbors(int v, int w) = 0;
    virtual int getNumVertices() = 0;
    virtual void initialize(Graph g, bool directed) = 0;
};

#endif