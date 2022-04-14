#include <stdexcept>
#include "Graph.h"

class VertexMatrix : public Graph {

    int** matrix;
    int size;

public:
    VertexMatrix();
    VertexMatrix(int* V, int n): matrix(V), size(n) {};
    ~VertexMatrix();
    bool areNeighbors(int v, int w);
};