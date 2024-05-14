//
// Created by yokoj on 12/05/2024.
//

#ifndef CREATE_HYPERGRAPH_GRAPH_H
#define CREATE_HYPERGRAPH_GRAPH_H

#include <iostream>
#include <algorithm>
#include <list>
#include <stack>
#include <unordered_map>
#include <unordered_set>

struct hashFunc {
    size_t operator()(const std::pair<int , int> &x) const{
        return x.first ^ x.second;
    }
};
class Graph {
private:
    int n = 0;
    int m = 0;
    std::unordered_set<int> vertices;
    std::unordered_set<std::pair<int, int>, hashFunc> edges;
    std::unordered_map<int,std::list<int>> adjacencyList;
    void inputGraphSize();
    void inputEdges();
    void DFS(const int &startNode, std::unordered_map<int, bool>& visited, std::list<int>& finishOrder);
public:
    void inputGraph();
    Graph makeEmptyGraph(const int& n);
    bool isAdjacent(const int &u, const int &v) const;
    std::list<int> getAdjList(const int &u) { return adjacencyList[u]; }
    void addEdge(const int &u, const int &v);
    void removeEdge(const int& u, const int& v);
    void transpose();
    Graph getHyperGraph();
};


#endif //CREATE_HYPERGRAPH_GRAPH_H
