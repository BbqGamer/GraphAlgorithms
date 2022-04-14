#ifndef VERTEXMATRIX_H
#define VERTEXMATRIX_H

#include <stdexcept>
#include "Graph.h"
#include <iostream>

class VertexMatrix : public Graph {

    int** matrix;
    int size;

public:
    VertexMatrix(): matrix{nullptr}, size(0) {};
    VertexMatrix(int** V, int numVertices): matrix(V), size(numVertices) {};
    ~VertexMatrix();

    bool areNeighbors(int v, int w);
    int getNumVertices();
};

#endif