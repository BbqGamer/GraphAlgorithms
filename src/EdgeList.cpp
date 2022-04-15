#include "EdgeList.h"

int EdgeList::getNumVertices() {
    return vList.size();
}

bool EdgeList::areNeighbors(int v, int w) {
    for (auto edge : eList) {
        if (edge.first == v && edge.second == w) {
            return true;
        }
    }
    return false;
}

void EdgeList::initialize(std::vector<int> vertexList, std::vector<std::pair<int, int>> edgeList, bool directed) {
    vList = vertexList;
    eList = edgeList;
}