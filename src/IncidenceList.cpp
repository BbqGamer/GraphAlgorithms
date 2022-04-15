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

void IncidenceList::initialize(std::vector<int> vertexList, std::vector<std::pair<int, int>> edgeList, bool directed) {
    iList = std::vector<std::vector<int>>();
    for(int i = 0; i < vertexList.size(); i++) {
        iList.push_back(std::vector<int>());
    }
    for(auto edge: edgeList) {
        iList[edge.first].push_back(edge.second);
        if(!directed) {
            iList[edge.second].push_back(edge.first);
        }
    }
}