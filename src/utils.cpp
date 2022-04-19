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