#ifndef EXPERIMENTS_H
#define EXPERIMENTS_H

#include "Graph.h"
#include "includes.h"
#include "utils.h"
#include "IncidenceList.h"

float measureLookup(GraphInterface* g, std::string file="graphs/graph.txt");
float measureTopSort(std::string file="graphs/graph.txt");

#endif