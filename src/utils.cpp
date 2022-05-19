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


int hasCycle(std::vector<std::pair<int, int>> &e, int edge, std::vector<bool> &visited, int v) {
    int i, x, sum;
    if (visited[v]) {
        return true;
    } else {
        visited[v] = true;
        sum = 0;
        for(i = edge; i >= 0; i--) {
            if(e[i].first == v) {
                sum += hasCycle(e, edge, visited, e[i].second);
            }
        }
    }

    visited[v] = false;
    if(sum == 0) {
        return false;
    } else {
        return true;
    }
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
        if(!hasCycle(edges, i, visited, edges[i].first) == true) {
            i++;
        }
    }
    g.edgeList = edges;
    return g;
}


void graphToDot(Graph g, std::string fileName, bool directed) {
    std::ofstream file;
    file.open(fileName);

    if (!file.is_open()) {
        throw std::runtime_error("Could not open file " + fileName);
    }

    std::string arc = " -- ";
    if (directed) {
        file << "digraph {\n";
        arc = " -> ";
    } else {
        file << "graph {\n";
        arc = " -- ";
    }

    for(int i = 0; i < g.edgeList.size(); i++) {
        file << "\t" << g.edgeList[i].first << arc << g.edgeList[i].second << ";\n";
    }

    file << "}\n";
}

//PART 2
Graph randomConnectedGraph(int numVertices, double saturation) {
    Graph g1 = randomSpanningTree(numVertices);
    IncidentMatrix g = IncidentMatrix(g1);

    int e = numVertices - 1;
    int numEdges = numVertices * (numVertices - 1) * saturation / 2;
    while(e < numEdges) {
        int v1 = rand() % numVertices;
        int v2 = rand() % numVertices;
        if(v1 != v2 && !g.areNeighbors(v1, v2)) {
            g.addEdge(v1, v2);
            g.addEdge(v2, v1);
            e++;
        }
    }
    return g.dumpGraph();
}

Graph randomSpanningTree(int numVertices) {
    std::vector<int> vertices;
    Graph g;
    for(int i = 0; i < numVertices; i++) {
        vertices.push_back(i);
        g.vertexList.push_back(i);
    }
    std::random_shuffle(vertices.begin(), vertices.end());
    
    srand(time(NULL));
    int parent;
    for(int i = 1; i < numVertices; i++) {
        parent = rand() % i;
        g.edgeList.push_back(std::pair<int, int>(vertices[i], vertices[parent]));
    }
    return g;
}

Graph randomEulerian(int numVertices, int saturation) {
    IncidenceList g = IncidenceList(randomConnectedGraph(numVertices, saturation));
    std::vector<int> oddVertices;
    std::vector<int> evenVertices;
    for(int i = 0; i < g.getNumVertices(); i++) {
        if(g.getNumEdges(i) % 2 == 1) {
            oddVertices.push_back(i);
        } else {
            evenVertices.push_back(i);
        }    
    }
    int numEdges = numVertices * (numVertices - 1) * saturation / 2;

    while(oddVertices.size()) {
        //Choose two random odd vertices
        int v1 = oddVertices[rand() % oddVertices.size()];
        int v2 = oddVertices[rand() % oddVertices.size()];
        if(g.areNeighbors(v1, v2)) {
            //TODO
        }
    }
    
    return g.dumpGraph();
}

Graph randomHamiltonianGraph(int numVertices, int saturation) {
    Graph g1 = randomSpanningTree(numVertices);
    IncidentMatrix g = IncidentMatrix(g1);

    int expected_number_of_edges = numVertices * (numVertices - 1) * saturation / 2;
    int numEdges = numVertices - 1;
    
    std::vector<int> path;
    for(int i = 0; i < numVertices; i++) {
        path.push_back(i);
    }

    //ADD PATH
    std::random_shuffle(path.begin(), path.end());
    for(int i = 0; i < numVertices - 1; i++) {
        g.addEdge(path[i], path[i + 1]);
        g.addEdge(path[i + 1], path[i]);
        numEdges += 1;
    }

    int v1;
    int v2;
    //ADD REMAINING EDGES
    while(numEdges < expected_number_of_edges) {
        v1 = rand() % numVertices;
        v2 = rand() % numVertices;
        if(v1 != v2 && !g.areNeighbors(v1, v2)) {
            g.addEdge(v1, v2);
            g.addEdge(v2, v1);
            numEdges += 1;
        }
    }

    return g.dumpGraph();
}