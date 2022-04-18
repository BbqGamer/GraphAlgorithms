#ifndef VERTEXMATRIX_H
#define VERTEXMATRIX_H

#include <stdexcept>
#include "Graph.h"
#include <iostream>
#include <vector>

class VertexMatrix : public Graph {

    std::vector<std::vector<int>> matrix;

public:
    VertexMatrix() {};
    VertexMatrix(std::vector<std::vector<int>> adjacencyMatrix);
    VertexMatrix(std::vector<int> vertexList, std::vector<std::pair<int, int>> edgeList, bool directed = 0) {
        initialize(vertexList, edgeList, directed);
    };

    bool areNeighbors(int v, int w);
    int getNumVertices();
    void initialize(std::vector<int> vertexList, std::vector<std::pair<int, int>> edgeList, bool directed = 0);
    bool operator==(const VertexMatrix &g) const;
};

#endif