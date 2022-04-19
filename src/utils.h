#ifndef UTILS_H
#define UTILS_H

#include "Graph.h"
#include "includes.h"

Graph readGraphFromFile(std::string fileName);
void writeGraphToFile(std::string fileName, Graph g);

Graph randomUndirectedGraph(int numVertices, double saturation);

#endif