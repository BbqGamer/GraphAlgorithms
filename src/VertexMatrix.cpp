#include "VertexMatrix.h"

VertexMatrix::~VertexMatrix() {
    if (matrix != nullptr) {
        for (int i = 0; i < size; i++) {
            delete[] matrix[i];
        }
    }
};

bool VertexMatrix::areNeighbors(int v, int w) {
    if(v <= size && w <= size) {
        return matrix[v][w] == 1;
    }
    throw std::out_of_range("Vertex out of bounds");
}