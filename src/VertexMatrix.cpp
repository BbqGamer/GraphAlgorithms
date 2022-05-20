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

void VertexMatrix::addEdge(int v1, int v2) {
    matrix[v1][v2] = 1;
    matrix[v2][v1] = 1;
}

bool VertexMatrix::areNeighbors(int v, int w) {
    if(v < getNumVertices() && w < getNumVertices() && v >= 0 && w >= 0) {
        return matrix[v][w] == 1;
    }
    throw std::out_of_range("Vertex out of bounds");
}

int VertexMatrix::getNumVertices() {
    return matrix.size();
}

void VertexMatrix::initialize(Graph g, bool directed) {
    matrix = std::vector<std::vector<int>>();
    for (int i = 0; i < g.vertexList.size(); i++) {
        std::vector<int> row;
        for (int j = 0; j < g.vertexList.size(); j++) {
            row.push_back(0);
        }
        matrix.push_back(row);
    }
    for(auto edge: g.edgeList) {
        matrix[edge.first][edge.second] = 1;
        if(!directed) {
            matrix[edge.second][edge.first] = 1;
        }
    }
}

Graph VertexMatrix::dumpGraph() {
    Graph g;
    for(int i = 0; i < matrix.size(); i++) {
        g.vertexList.push_back(i);
    }
    for(int i = 0; i < matrix.size(); i++) {
        for(int j = i + 1; j < matrix[i].size(); j++) {
            if(matrix[i][j] == 1) {
                g.edgeList.push_back(std::pair<int, int>(i, j));
            }
        }
    }
    return g;
}

bool VertexMatrix::operator==(const VertexMatrix &g) const {
    return g.matrix == matrix;
}