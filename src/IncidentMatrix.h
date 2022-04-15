#ifndef INCIDENTMATRIX_H
#define INCIDENTMATRIX_H

#include <stdexcept>
#include "Graph.h"
#include <iostream>
#include <vector>

class IncidentMatrix : public Graph {

    std::vector<std::vector<int>> matrix;

public:
    IncidentMatrix() {};
    IncidentMatrix(std::vector<std::vector<int>> incidentMatrix);

    bool areNeighbors(int v, int w);
    int getNumVertices();
    void initialize(std::vector<int> vertexList, std::vector<std::pair<int, int>> edgeList);
};

#endif