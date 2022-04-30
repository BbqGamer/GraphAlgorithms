#ifndef GRAPH_H
#define GRAPH_H

#include<vector>
#include<string>

typedef struct Graphtag {
    std::vector<int> vertexList;
    std::vector<std::pair<int, int>> edgeList;
} Graph;

class GraphInterface {
public:
    virtual bool areNeighbors(int v, int w) = 0;
    virtual int getNumVertices() = 0;

    virtual void initialize(Graph g, bool directed) = 0;
    virtual Graph dumpGraph() = 0;

    virtual std::string getName() = 0;
};

#endif