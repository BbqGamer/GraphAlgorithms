#include "experiments.h"
#include <time.h>

float measureLookup(GraphInterface* g, std::string file) {
    clock_t start, end;
    float totalTime = 0;

    Graph gf = readGraphFromFile(file);
    g->initialize(gf, false);
    for(int i = 0; i < g->getNumVertices(); i++) {
        for(int j = 0; j < g->getNumVertices(); j++) {
            start = clock();

            //LOOKUP
            g->areNeighbors(i, j);

            end = clock();
            totalTime += (float)(end - start) / CLOCKS_PER_SEC;
        }
    }
    return totalTime/(g->getNumVertices());
}

float measureTopSort(std::string file) {
    IncidenceList graph = IncidenceList(readGraphFromFile(file), 1);
    
    clock_t start = clock();

    graph.topologicalSort();

    return (float)(clock() - start) / CLOCKS_PER_SEC;
}