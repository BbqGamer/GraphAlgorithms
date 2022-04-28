#include "utils.h"

Graph readGraphFromFile(std::string fileName) {
    std::ifstream file;
    file.open(fileName);

    if (!file.is_open()) {
        throw std::runtime_error("Could not open file " + fileName);
    }
    
    int numVertices, v;
    file >> numVertices;
    std::vector<int> vertices;
    for(int i = 0; i < numVertices; i++) {
        file >> v;
        vertices.push_back(v);
    }
    int numEdges, e1, e2;
    file >> numEdges;
    std::vector<std::pair<int, int>> edges;
    for(int i = 0; i < numEdges; i++) {
        file >> e1;
        file >> e2;
        edges.push_back(std::pair<int, int>(e1, e2));
    }

    Graph g;
    g.vertexList = vertices;
    g.edgeList = edges;
    
    file.close();
    return g;
}

void writeGraphToFile(std::string fileName, Graph g) {
    std::ofstream file;
    file.open(fileName);

    if (!file.is_open()) {
        throw std::runtime_error("Could not open file " + fileName);
    }

    file << g.vertexList.size() << std::endl;
    for(int i = 0; i < g.vertexList.size(); i++) {
        file << g.vertexList[i] << " ";
    }
    file << std::endl;

    file << g.edgeList.size() << std::endl;
    for(int i = 0; i < g.edgeList.size(); i++) {
        file << g.edgeList[i].first << " " << g.edgeList[i].second << std::endl;
    }
}

Graph randomUndirectedGraph(int numVertices, double saturation) {
    Graph g;
    std::vector<int> vertices;
    for(int i = 0; i < numVertices; i++) {
        vertices.push_back(i);
    }
    g.vertexList = vertices;

    std::vector<std::pair<int, int>> possibleEdges;
    for(int i = 0; i < numVertices; i++) {
        for(int j = i + 1; j < numVertices; j++) {
            possibleEdges.push_back(std::pair<int, int>(i, j));
        }
    }

    std::random_shuffle(possibleEdges.begin(), possibleEdges.end());
    possibleEdges.resize((numVertices * (numVertices - 1) / 2) * saturation);
    g.edgeList = possibleEdges;

    return g;
}


int isAcyclic(std::vector<std::pair<int, int>> &e, int edge, std::vector<bool> &visited, int v) {
    int i, x;
    if (visited[v]) {
        return false;
    } else {
        visited[v] = true;
        for(i = edge; i >= 0; i--) {
            x = isAcyclic(e, edge, visited, e[i].second);
            if (x != -1) {
                return x;
            }
        }
    }
    visited[v] = false;

    if(i == 0) {
        return true;
    }
    return -1;
}

Graph randomDAC(int numVertices, double saturation) {
    Graph g;
    srand(time(NULL));
    std::vector<int> vertices;
    for(int i = 0; i < numVertices; i++) {
        vertices.push_back(i);
    }
    g.vertexList = vertices;

    int numEdges = (numVertices * (numVertices - 1)) / 2 * saturation;
    std::vector<std::pair<int, int>> edges(numEdges, std::pair<int, int>(-1, -1));
    std::vector<bool> visited(numVertices, false);

    int i = 0;
    while(i < numEdges) {
        edges[i].first = rand() % numVertices;
        edges[i].second = rand() % numVertices;
        for(int j = 0; j < numVertices; j++) {
            visited[j] = false;
        }
        if(isAcyclic(edges, i, visited, edges[i].first) == true) {
            i++;
        }
    }
    g.edgeList = edges;
    return g;
}
