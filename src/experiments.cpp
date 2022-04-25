#include "experiments.h"

void measureLookup(GraphInterface* g, std::string file) {
    Graph gf = readGraphFromFile(file);
    g->initialize(gf, false);
    for(int i = 0; i < g->getNumVertices(); i++) {
        for(int j = 0; j < g->getNumVertices(); j++) {
            if(g->areNeighbors(i, j)) {
                std::cout << "(" << i << ", " << j << ") ";
            }
        }
        std::cout << std::endl;
    }
}