#ifndef UTILS_H
#define UTILS_H

#include "Graph.h"
#include "includes.h"
#include "IncidentMatrix.h"
#include "IncidenceList.h"
#include "VertexMatrix.h"

Graph readGraphFromFile(std::string fileName);
void writeGraphToFile(std::string fileName, Graph g);

void graphToDot(Graph g, std::string fileName, bool directed=0);

Graph randomUndirectedGraph(int numVertices, double saturation);
Graph randomDAC(int numVertices, double saturation);
int hasCycle(std::vector<std::pair<int, int>> &e, int edge, std::vector<bool> &visited, int v);

//PART 2
Graph randomConnectedGraph(int numVertices, double saturation);
Graph randomSpanningTree(int numVertices);
Graph randomEulerianGraph(int numVertices, double saturation);
Graph randomHamiltonianGraph(int numVertices, double saturation);

std::vector<int> findEulerianCycle(Graph graph);
std::vector<int> findHamiltonianCycle(Graph graph);
bool backtrackingHamiltonian(IncidenceList& graph, std::vector<int>& path);
std::vector<int> findHamiltonianCycle_wrapper(Graph graph);


#endif