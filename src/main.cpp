#include <iostream>
#include "includes.h"
#include "utils.h"
#include "experiments.h"
#include "VertexMatrix.h"
#include "IncidentMatrix.h"
#include "IncidenceList.h"
#include "EdgeList.h"

#include <chrono>
#include <unistd.h>


void generateGraphs(int start, int end, int step, float saturation = 0.6, bool DAGs = 0) {
    for(int n = start; n <= end; n += step) {
        std::cout << "Generating graph with n = " << n << std::endl;
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
    //TOPSORT
    std::ofstream file;
    file.open("../data/csv/topsortFINAL.csv");
    file << "n,time" << std::endl;

    for(int n = start; n <= end; n += step) {
        std::cout << "n = " << n << std::endl;
        std::string filename = "../data/txt/DAG-" + std::to_string(n) + ".txt";
        float timeTaken = measureTopSort(filename);
        file << n << "," << timeTaken << std::endl;
    }    
}


void eulerexp(int start, int end, int step, int repeats=10) {
    std::ofstream file;
    file.open("../data/csv/euler.csv");
    file << "n,k,time\n";

    std::vector<double> saturations = {0.2, 0.3, 0.4, 0.6, 0.8, 0.95};
    time_t begin, finish;

    for(int n = start; n <= end; n += step) {
        for(auto k : saturations) {
            for(int i = 0; i < repeats; i++) {
                std::cout << "Generating graph with " << n << " edges, and saturation: " << k << std::endl;
                Graph g = randomEulerianGraph(n , k);

                std::cout << "Finding eulerian circuit" << std::endl;
                auto begin = std::chrono::high_resolution_clock::now();

                findEulerianCycle(g);
            
                auto finish = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::microseconds>(finish - begin);
                file << n << "," << k << "," << duration.count() << "\n";
            }
        }
    }

    file.close();
}

void hamiltonexp(int start, int end, int step, int repeats=10) {
    std::ofstream file;
    file.open("../data/csv/hamiltonFINAL.csv");
    file << "n,k,time\n";
    file.close();

    //std::vector<double> saturations = {0.95, 0.8, 0.6};
    std::vector<double> saturations = {0.95, 0.8, 0.6, 0.4, 0.3, 0.2};
    time_t begin, finish;

    for(int i = 0; i < repeats; i++) {
        for(auto k : saturations) {    
            for(int n = start; n <= end; n += step) {
                file.open("../data/csv/hamiltonFINAL.csv", std::ios_base::app);
                std::cout << "Generating graph with " << n << " edges, and saturation: " << k << std::endl;
                Graph g = randomHamiltonianGraph(n , k);
                //graphToDot(g, "../data/dot/current.dot");

                std::cout << "Finding hamiltonian cycle" << std::endl;

                auto begin = std::chrono::high_resolution_clock::now();

                bool timeout = false;
                try {
                    findHamiltonianCycle_wrapper(g);
                } catch (std::runtime_error e) {
                    std::cout << "Error: " << e.what() << std::endl;
                    timeout = true;
                }
                
                auto finish = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::microseconds>(finish - begin);
                file << n << "," << k << "," << duration.count() << "\n";
                file.close();
            }
        }
    }
    file.close();
}


int main() {

    //EXP 1
    //generateGraphs(850, 2000, 50, 0.6, 0);
    //exp1(850, 2000, 50);

    // generateGraphs(100, 10001, 500, 0.3, 1);
    // exp2(100, 10000, 500);

    //EXP 2
    //generateGraphs(100, 2000, 100, 0.3, 1);
    //exp2(100, 2000, 100);
    // Graph g = randomGraphWithCycles(20, 0.2);
    // graphToDot(g , "../data/dot/hamilton.dot", 0);
    // for(auto a : findHamiltonianCycle(g)) {
    //     std::cout << a << " ";
    // }
    
    hamiltonexp(200, 1001, 200, 25);
    //eulerexp(200, 2000, 50);

    return 0;
}