#ifndef INCIDENCELIST_H
#define INCIDENCELIST_H

#include <stdexcept>
#include "Graph.h"
#include <iostream>
#include <vector>
#include <stack>

class IncidenceList : public GraphInterface {

    std::vector<std::vector<int>> iList;

    void topsortRec(int v, std::vector<bool> &visited, std::stack<int>& s);
public:
    IncidenceList() {};
    IncidenceList(std::vector<std::vector<int>> incidenceList): iList(incidenceList) {};
    IncidenceList(Graph g, bool directed = 0) {
        initialize(g, directed);
    };

    bool areNeighbors(int v, int w);
    int getNumVertices();
    int getNumEdges(int v);
    std::vector<int>& getNeighbours(int vertex);
    int popNeighbor(int vertex);

    void removeEdge(int v, int w);
    
    void initialize(Graph g, bool directed=0);
    Graph dumpGraph();
 
    std::vector<int> topologicalSort();

    bool operator==(const IncidenceList &g) const;

    std::string getName() {return "Incidence List";}
};

#endif