#ifndef VERTEXMATRIX_H
#define VERTEXMATRIX_H

#include "Graph.h"
#include "includes.h"

class VertexMatrix : public GraphInterface {

    std::vector<std::vector<int>> matrix;

public:
    VertexMatrix() {};
    VertexMatrix(std::vector<std::vector<int>> adjacencyMatrix);
    VertexMatrix(Graph g, bool directed = 0) {
        initialize(g, directed);
    };

    bool areNeighbors(int v, int w);
    int getNumVertices();
    void addEdge(int v1, int v2);
    
    void initialize(Graph g, bool directed = 0);
    Graph dumpGraph();

    bool operator==(const VertexMatrix &g) const;

    std::string getName() {return "Vertex Matrix";}
};

#endif