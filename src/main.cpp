#include <iostream>
#include "includes.h"
#include "utils.h"
#include "experiments.h"
#include "VertexMatrix.h"
#include "IncidentMatrix.h"
#include "IncidenceList.h"
#include "EdgeList.h"


void generateGraphs(int start, int end, int step, float saturation = 0.6, bool DAGs = 0) {
    for(int n = start; n <= end; n += step) {
        if(!DAGs) {
            std::string filename = "../data/txt/undirected-" + std::to_string(n) + ".txt";
            writeGraphToFile(filename, randomUndirectedGraph(n, saturation));
        } else {
            std::string filename = "../data/txt/DAG-" + std::to_string(n) + ".txt";
            writeGraphToFile(filename, randomUndirectedGraph(n, 0.6));
        }
    }
}

void exp1(int start, int end, int step) {
    //std::vector<GraphInterface*> graphRepresentations = {new VertexMatrix(), new IncidentMatrix(), new IncidenceList(), new EdgeList()};
    std::vector<GraphInterface*> graphRepresentations = {new VertexMatrix(), new IncidenceList()};

    std::ofstream file;
    file.open("../data/csv/lookup.csv");
    file << "repr,n,time" << std::endl;

    float averageTime;

    for(int n = start; n <= end; n += step) {
        std::string filename = "../data/txt/undirected-" + std::to_string(n) + ".txt";
        for(int i = 0; i < graphRepresentations.size(); i++) {

            averageTime = measureLookup(graphRepresentations[i], filename);
            file << graphRepresentations[i]->getName() << "," << n << "," << averageTime << std::endl;

        }
    }
}

void exp2(int start, int end, int step) {
    std::ofstream file;
    file.open("../data/csv/topsort.csv");
    file << "n,time" << std::endl;

    for(int n = start; n <= end; n += step) {
        std::string filename = "../data/txt/DAG-" + std::to_string(n) + ".txt";
        float timeTaken = measureTopSort(filename);
        file << n << "," << timeTaken << std::endl;
    }    
}


int main() {

    //EXP 1
    //generateGraphs(850, 2000, 50, 0.6, 0);
    //exp1(850, 2000, 50);

    //EXP 2
    //generateGraphs(100, 2000, 100, 0.3, 1);
    //exp2(100, 2000, 100);
    graphToDot(randomHamiltonianGraph(100, 0.5), "../data/dot/hamilton.dot", 0);
    
    return 0;
}