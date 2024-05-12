//
// Created by yokoj on 12/05/2024.
//

#ifndef CREATE_HYPERGRAPH_GRAPH_H
#define CREATE_HYPERGRAPH_GRAPH_H

#include <iostream>
#include <list>
#include <algorithm>
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
    std::unordered_map<int,std::list<int>> map;
    void inputGraphSize();
    void inputEdges();
public:
    Graph();
    void inputGraph();
    void makeEmptyGraph(const int& n);
    bool isAdjacent(const int &u, const int &v) const;
    std::list<int> getAdjList(const int &u) { return map[u]; }
    void addEdge(const int &u, const int &v);
    void removeEdge(const int& u, const int& v);
};


#endif //CREATE_HYPERGRAPH_GRAPH_H
