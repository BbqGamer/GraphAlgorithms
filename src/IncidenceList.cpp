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

int IncidenceList::getNumEdges(int v) {
    return iList[v].size();
}

std::vector<int>& IncidenceList::getNeighbours(int vertex) {
    return iList[vertex];
}

int IncidenceList::popNeighbor(int vertex) {
    int v = iList[vertex][0];
    this->removeEdge(vertex, v);
    return v;
}

void IncidenceList::removeEdge(int v, int w) {
    for(int i = 0; i < iList[v].size(); i++) {
        if(iList[v][i] == w) {
            iList[v].erase(iList[v].begin() + i);
            break;
        }
    }

    for(int i = 0; i < iList[w].size(); i++) {
        if(iList[w][i] == v) {
            iList[w].erase(iList[w].begin() + i);
            break;
        }
    }
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

void IncidenceList::topsortRec(int v, std::vector<bool> &visited, std::stack<int>& s) {
    visited[v] = true;
    for(auto w: iList[v]) {
        if(!visited[w]) {
            topsortRec(w, visited, s);
        }
    }

    s.push(v);
}

std::vector<int> IncidenceList::topologicalSort() {
    std::stack<int> s;
    std::vector<bool> visited = std::vector<bool>(getNumVertices(), false);

    for (int i = 0; i < getNumVertices(); i++)
        if (!visited[i]) {
            topsortRec(i, visited, s);
        }
        
    std::vector<int> topologicalOrder;
    while(!s.empty()) {
        topologicalOrder.push_back(s.top());
        s.pop();
    }

    return topologicalOrder;
}