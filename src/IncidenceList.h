#ifndef INCIDENCELIST_H
#define INCIDENCELIST_H

#include <stdexcept>
#include "Graph.h"
#include <iostream>
#include <vector>

class IncidenceList : public GraphInterface {

    std::vector<std::vector<int>> iList;

public:
    IncidenceList() {};
    IncidenceList(std::vector<std::vector<int>> incidenceList): iList(incidenceList) {};
    IncidenceList(Graph g, bool directed = 0) {
        initialize(g, directed);
    };

    bool areNeighbors(int v, int w);
    int getNumVertices();
    void initialize(Graph g, bool directed=0);
    bool operator==(const IncidenceList &g) const;
};

#endif