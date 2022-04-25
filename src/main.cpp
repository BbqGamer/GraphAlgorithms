#include <iostream>
#include "includes.h"
#include "utils.h"
#include "experiments.h"
#include "VertexMatrix.h"
#include "IncidentMatrix.h"
#include "IncidenceList.h"
#include "EdgeList.h"

int main() {

    std::vector<GraphInterface*> graphRepresentations = {new VertexMatrix(), new IncidentMatrix(), new IncidenceList(), new EdgeList()};
    
    writeGraphToFile("../tst/data/bigGraph.txt", randomUndirectedGraph(100, 0.6));
    for(int i = 0; i < graphRepresentations.size(); i++) {
        measureLookup(graphRepresentations[i], "../tst/data/bigGraph.txt"); 
    }

    return 0;
}

