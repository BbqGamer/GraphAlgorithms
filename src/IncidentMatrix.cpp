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

void IncidentMatrix::addEdge(int v, int w) {
    if(v < getNumVertices() && w < getNumVertices() && v >= 0 && w >= 0) {
        matrix[v][w] = 1;
        matrix[w][v] = 1;
    }
    else {
        throw std::out_of_range("Vertex out of bounds");
    }
}

void IncidentMatrix::initialize(Graph g, bool directed) {
    matrix = std::vector<std::vector<int>>();
    for(int i = 0; i < g.vertexList.size(); i++) {
        matrix.push_back(std::vector<int>(g.vertexList.size(), 0));
    }
    for(auto edge: g.edgeList) {
        if(!directed) {
            matrix[edge.first][edge.second] = 1;
            matrix[edge.second][edge.first] = 1;
        } else {
            matrix[edge.first][edge.second] = -1;
            matrix[edge.second][edge.first] = 1;
        }
    }
}

Graph IncidentMatrix::dumpGraph() {
    Graph g;
    for(int i = 0; i < matrix.size(); i++) {
        g.vertexList.push_back(i);
    }
    for(int i = 0; i < matrix.size(); i++) {
        for(int j = i + 1; j < matrix.size(); j++) {
            if(matrix[i][j] == 1) {
                g.edgeList.push_back(std::pair<int, int>(i, j));
            }
        }
    }

    return g;
}

bool IncidentMatrix::operator==(const IncidentMatrix &g) const {
    return g.matrix == matrix;
}