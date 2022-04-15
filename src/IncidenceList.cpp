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