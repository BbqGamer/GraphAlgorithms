#include "VertexMatrix.h"

VertexMatrix::VertexMatrix(std::vector<std::vector<int>> adjacencyMatrix) {
    if (adjacencyMatrix.size() == 0) {
        throw std::invalid_argument("Adjacency matrix cannot be empty");
    }
    if (adjacencyMatrix[0].size() == 0) {
        throw std::invalid_argument("Adjacency matrix cannot be empty");
    }
    for (int i = 0; i < adjacencyMatrix.size(); i++) {
        if (adjacencyMatrix[i].size() != adjacencyMatrix.size()) {
            throw std::invalid_argument("Adjacency matrix must be square");
        }
    }
    matrix = adjacencyMatrix;
};

bool VertexMatrix::areNeighbors(int v, int w) {
    if(v < getNumVertices() && w < getNumVertices() && v >= 0 && w >= 0) {
        return matrix[v][w] == 1;
    }
    throw std::out_of_range("Vertex out of bounds");
}

int VertexMatrix::getNumVertices() {
    return matrix.size();
}

void VertexMatrix::initialize(std::vector<int> vertexList, std::vector<std::pair<int, int>> edgeList, bool directed) {
    std::vector<std::vector<int>> adjacencyMatrix;
    for (int i = 0; i < vertexList.size(); i++) {
        std::vector<int> row;
        for (int j = 0; j < vertexList.size(); j++) {
            row.push_back(0);
        }
        adjacencyMatrix.push_back(row);
    }
    for(auto edge: edgeList) {
        adjacencyMatrix[edge.first][edge.second] = 1;
        adjacencyMatrix[edge.second][edge.first] = 1;
    }
}
