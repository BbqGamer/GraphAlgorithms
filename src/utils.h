#ifndef UTILS_H
#define UTILS_H

#include "Graph.h"
#include "includes.h"

Graph readGraphFromFile(std::string fileName);
void writeGraphToFile(std::string fileName, Graph g);

Graph randomUndirectedGraph(int numVertices, double saturation);
Graph randomDAC(int numVertices, double saturation);
int hasCycle(std::vector<std::pair<int, int>> &e, int edge, std::vector<bool> &visited, int v);

#endif