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
    
    bool areNeighbors(int v, int w);
    int getNumVertices();
};

#endif