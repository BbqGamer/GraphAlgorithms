#include "IncidentMatrix.h"

IncidentMatrix::IncidentMatrix(std::vector<std::vector<int>> incidentMatrix) {
    if (incidentMatrix.size() == 0) {
        throw std::invalid_argument("Incident matrix cannot be empty");
    }
    if (incidentMatrix[0].size() == 0) {
        throw std::invalid_argument("Incident matrix cannot be empty");
    }
    for (int i = 1; i < incidentMatrix.size(); i++) {
        if (incidentMatrix[i].size() != incidentMatrix[0].size()) {
            throw std::invalid_argument("Incident matrix must be a rectangle");
        }
    }
    matrix = incidentMatrix;
};

bool IncidentMatrix::areNeighbors(int v, int w) {
    if(v < getNumVertices() && w < getNumVertices() && v >= 0 && w >= 0) {
        for(int i = 0; i < matrix[v].size(); i++) {
            if(matrix[v][i] == 1 && matrix[w][i] == 1) {
                return true;
            }
        }
        return false;
    }
    throw std::out_of_range("Vertex out of bounds");
}

int IncidentMatrix::getNumVertices() {
    return matrix.size();
}

void IncidentMatrix::initialize(std::vector<int> vertexList, std::vector<std::pair<int, int>> edgeList, bool directed) {
    return;
}