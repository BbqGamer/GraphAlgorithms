#ifndef INCIDENTMATRIX_H
#define INCIDENTMATRIX_H

#include "includes.h"
#include "Graph.h"

class IncidentMatrix : public GraphInterface {

    std::vector<std::vector<int>> matrix;

public:
    IncidentMatrix() {};
    IncidentMatrix(std::vector<std::vector<int>> incidentMatrix);
    IncidentMatrix(Graph g, bool directed = 0) {
        initialize(g, directed);
    };

    bool areNeighbors(int v, int w);
    int getNumVertices();
    void initialize(Graph g, bool directed = 0);
    bool operator==(const IncidentMatrix &g) const;

    std::string getName() {return "Incident Matrix";}
};

#endif