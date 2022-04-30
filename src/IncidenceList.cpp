#include "IncidenceList.h"

bool IncidenceList::areNeighbors(int v, int w) {
    if(v < getNumVertices() && w < getNumVertices() && v >= 0 && w >= 0) {
        for(int i = 0; i < iList[v].size(); i++) {
            if(iList[v][i] == w) {
                return true;
            }
        }
        return false;
    }
    throw std::out_of_range("Vertex out of bounds");
}

int IncidenceList::getNumVertices() {
    return iList.size();
}

void IncidenceList::initialize(Graph g, bool directed) {
    iList = std::vector<std::vector<int>>();
    for(int i = 0; i < g.vertexList.size(); i++) {
        iList.push_back(std::vector<int>());
    }
    for(auto edge: g.edgeList) {
        iList[edge.first].push_back(edge.second);
        if(!directed) {
            iList[edge.second].push_back(edge.first);
        }
    }
}

Graph IncidenceList::dumpGraph() {
    Graph g;
    g.vertexList = std::vector<int>();
    for(int i = 0; i < this->getNumVertices(); i++) {
        g.vertexList.push_back(i);
    }
    g.edgeList = std::vector<std::pair<int, int>>();
    for(int i = 0; i < this->getNumVertices(); i++) {
        for(int j = 0; j < iList[i].size(); j++) {
            g.edgeList.push_back(std::pair<int, int>(i, iList[i][j]));
        }
    }
    return g;
}

bool IncidenceList::operator==(const IncidenceList &g) const {
    return g.iList == iList;
}