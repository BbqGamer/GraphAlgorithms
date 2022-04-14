#include <stdexcept>
#include "Graph.h"
#include <iostream>

class VertexMatrix : public Graph {

    int** matrix;
    int size;

public:
    VertexMatrix(): matrix{nullptr}, size(0) {};
    VertexMatrix(int** V, int n): matrix(V), size(n) {};
    ~VertexMatrix();
    bool areNeighbors(int v, int w);
};