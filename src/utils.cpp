#include "utils.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>
#include <condition_variable>

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
    
    file.close();
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
    file.close();
}

//PART 2
Graph randomConnectedGraph(int numVertices, double saturation) {
    Graph g1 = randomSpanningTree(numVertices);
    VertexMatrix g = VertexMatrix(g1);

    int e = numVertices - 1;
    int numEdges = numVertices * (numVertices - 1) * saturation / 2;
    while(e < numEdges) {
        int v1 = rand() % numVertices;
        int v2 = rand() % numVertices;
        if(v1 != v2 && !g.areNeighbors(v1, v2)) {
            g.addEdge(v1, v2);
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

#define EULER_TIMEOUT 100
Graph randomEulerianGraph(int numVertices, double saturation) {
    VertexMatrix g = VertexMatrix(randomSpanningTree(numVertices));

    int expected_number_of_edges = saturation * (numVertices * (numVertices - 1) / 2);
    int numEdges = numVertices;

    int v1, v2, v3;
    //ADD REMAINING EDGES while preserving eulerian cycle conditions
    
    time_t start = clock();

    while(numEdges < expected_number_of_edges) {
        v1 = rand() % numVertices;
        v2 = rand() % numVertices;
        v3 = rand() % numVertices;
        if(v1 != v2 && v2 != v3 && v3 != v1
            && !g.areNeighbors(v1, v2)
            && !g.areNeighbors(v2, v3)
            && !g.areNeighbors(v3, v1)
            ) {
                g.addEdge(v1, v2);
                g.addEdge(v2, v3);
                g.addEdge(v3, v1);
                numEdges += 3;
        }
        if(float(clock() - start) / CLOCKS_PER_SEC > EULER_TIMEOUT) {
            std::cout << "TIMEOUT in Euler cycle creation" << std::endl;
            break;
        }
    }

    return g.dumpGraph();
}

Graph randomHamiltonianGraph(int numVertices, double saturation) {
    std::vector<int> vertices;
    for(int i = 0; i < numVertices; i++) {
        vertices.push_back(i);
    }

    Graph G;
    G.vertexList = vertices;
    G.edgeList = std::vector<std::pair<int, int>>();
    VertexMatrix g = VertexMatrix(G);

    //ADD HAMILTON PATH
    std::cout << "  Adding hamiltonian path" << std::endl;
    std::random_shuffle(vertices.begin(), vertices.end());
    for(int i = 0; i < numVertices - 1; i++) {
        g.addEdge(vertices[i], vertices[i + 1]);
    }
    g.addEdge(vertices[numVertices - 1], vertices[0]);

    int expected_number_of_edges = saturation * (numVertices * (numVertices - 1) / 2);
    int numEdges = numVertices;

    int v1, v2;
    //ADD REMAINING EDGES
    std::cout << "  Adding remaining edges" << std::endl;
    while(numEdges < expected_number_of_edges) {
        v1 = rand() % numVertices;
        v2 = rand() % numVertices;
        if(v1 != v2 && !g.areNeighbors(v1, v2)) {
            g.addEdge(v1, v2);
            numEdges++;
        }
    }
    
    std::cout << "  Dumping graph" << std::endl;
    return g.dumpGraph();
}


std::vector<int> findEulerianCycle(Graph graph) {
    IncidenceList g = IncidenceList(graph);

    int n;
    std::vector<int> cycle;
    std::stack<int> s;
    s.push(0);
    while(!s.empty()) {
        if(g.getNumEdges(s.top())) {
            s.push(g.popNeighbor(s.top()));
        } else {
            cycle.push_back(s.top());
            s.pop();            
        }
    }

    return cycle;
}


std::vector<int> findHamiltonianCycle_wrapper(Graph graph) {

    std::mutex m;
    std::condition_variable cv;
    std::vector<int> retValue;

    std::thread t([&cv, &retValue, &graph]()
    {
        retValue = findHamiltonianCycle(graph);
        cv.notify_one();
    });

    t.detach();

    {
        std::chrono::seconds TIMEOUT(300);
        std::unique_lock<std::mutex> l(m);
        if(cv.wait_for(l, TIMEOUT) == std::cv_status::timeout) 
            throw std::runtime_error("Timeout");
    }

    return retValue; 
}

std::vector<int> findHamiltonianCycle(Graph graph) {
    IncidenceList g = IncidenceList(graph);
    std::vector<int> path;
    path.push_back(0);

    if(backtrackingHamiltonian(g, path)) {
        path.push_back(0);
        return path;
    } else {
        return std::vector<int>();
    }
}

bool backtrackingHamiltonian(IncidenceList& graph, std::vector<int>& path) {
    int u = path[path.size() - 1];
    if(path.size() == graph.getNumVertices()) {
        int v = path[0];
        if(graph.areNeighbors(u, v))
            return true;
        return false;
    }
    for(auto v : graph.getNeighbours(u)) {
        if(std::find(path.begin(), path.end(), v) == path.end()) {
            path.push_back(v);
            if(backtrackingHamiltonian(graph, path))
                return true;
            path.pop_back();
        }
    }
    return false;
}