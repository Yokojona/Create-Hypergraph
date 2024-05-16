#include "Graph.h"

int main() {
    // 8 13 0 1 0 3 1 2 2 0 2 3 2 5 3 1 4 1 4 2 4 5 5 7 7 6 6 5
    // 6 10 1 2 1 3 2 3 2 4 4 3 3 5 5 4 5 6 4 6 2 6
    Graph graph;
    graph.inputGraph();
    Graph hyperGraph = graph.getHyperGraph();
    hyperGraph.printSize();
}
