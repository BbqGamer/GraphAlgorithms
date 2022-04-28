#include <iostream>
#include "includes.h"
#include "utils.h"
#include "experiments.h"
#include "VertexMatrix.h"
#include "IncidentMatrix.h"
#include "IncidenceList.h"
#include "EdgeList.h"

#define START 100
#define END 800
#define STEP 50
#define OUT_FILE "../data/lookup2.csv"

int main() {

    // //GENERATE GRAPH FILES
    // for(int n = START; n <= END; n += STEP) {
    //     std::string filename = "../data/graphs/undirected-" + std::to_string(n) + ".txt";
    //     writeGraphToFile(filename, randomUndirectedGraph(n, 0.6));
    // }

    std::vector<GraphInterface*> graphRepresentations = {new VertexMatrix(), new IncidentMatrix(), new IncidenceList(), new EdgeList()};
    
    std::ofstream file;
    file.open(OUT_FILE);
    file << "repr,n,time" << std::endl;

    float averageTime;

    for(int n = START; n <= END; n += STEP) {
        std::string filename = "../data/graphs/undirected-" + std::to_string(n) + ".txt";
        for(int i = 0; i < graphRepresentations.size(); i++) {

            averageTime = measureLookup(graphRepresentations[i], filename);
            file << graphRepresentations[i]->getName() << "," << n << "," << averageTime << std::endl;

        }
    }

    return 0;
}