#ifndef INCIDENTMATRIX_H
#define INCIDENTMATRIX_H

#include <stdexcept>
#include "Graph.h"
#include <iostream>

class IncidentMatrix : public Graph {

    int** matrix;
    int size;
    int edges;

public:
    IncidentMatrix(): matrix{nullptr}, size(0), numEdges(0) {};
    IncidentMatrix(int** V, int numVertices, int numEdges): matrix(V), size(numVertices), edges(numEdges) {};
    ~IncidentMatrix();
    bool areNeighbors(int v, int w);
    int getNumVertices();
};

#endif