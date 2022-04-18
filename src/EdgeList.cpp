#include "EdgeList.h"

int EdgeList::getNumVertices() {
    return vertexList.size();
}

bool EdgeList::areNeighbors(int v, int w) {
    for (auto edge : edgeList) {
        if (edge.first == v && edge.second == w) {
            return true;
        }
    }
    return false;
}

void EdgeList::initialize(Graph g, bool directed) {
    vertexList = g.vertexList;
    edgeList = g.edgeList;
    if(!directed) {
        std::cout <<"HI"<<std::endl;
        for(auto edge: g.edgeList) {
            edgeList.push_back(std::pair<int, int>(edge.second, edge.first));
        }
    }
}

bool EdgeList::operator==(const EdgeList &g) const {
    return g.vertexList == vertexList && g.edgeList == edgeList;
}