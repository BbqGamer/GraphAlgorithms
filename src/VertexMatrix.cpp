#include "VertexMatrix.h"

VertexMatrix::~VertexMatrix() {
    if (matrix != nullptr && size > 0) {
        for(int i = 0; i < size; i++) {
            delete[] matrix[i];
        }
        delete[] matrix;
    }
};

bool VertexMatrix::areNeighbors(int v, int w) {
    if(v < size && w < size && v >= 0 && w >= 0) {
        return matrix[v][w] == 1;
    }
    throw std::out_of_range("Vertex out of bounds");
}

int VertexMatrix::getNumVertices() {
    return size;
}