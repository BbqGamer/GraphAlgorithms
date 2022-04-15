#ifndef INCIDENCELIST_H
#define INCIDENCELIST_H

#include <stdexcept>
#include "Graph.h"
#include <iostream>
#include <vector>

class IncidenceList : public Graph {

    std::vector<std::vector<int>> iList;

public:
    IncidenceList() {};
    IncidenceList(std::vector<std::vector<int>> incidenceList): iList(incidenceList) {};

    bool areNeighbors(int v, int w);
    int getNumVertices();
    void initialize(std::vector<int> vertexList, std::vector<std::pair<int, int>> edgeList, bool directed=0);
    bool operator==(const IncidenceList &g) const;
};

#endif