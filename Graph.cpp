//
// Created by yokoj on 12/05/2024.
//
#include "Graph.h"

Graph::Graph() {
    inputGraph();
}

void Graph::inputGraph() {
    inputGraphSize();
    inputEdges();
    for (auto v : vertices) {
        for (auto e : edges) {
            if (e.first == v) {
                map[v].push_front(e.second);
            }
        }
        if (map.find(v) == map.end())
            map[v] = {};
    }
}

void Graph::inputGraphSize() {
    char *endPtr;
    std::string s;
    std::cout << "Number of vertices:" << std::endl;
    std::cin >> s;
    n = strtol(s.c_str(), &endPtr, 10);
    if (*endPtr != '\0' || n < 0 || n > INT_MAX) {
        std::cout << "invalid input" << std::endl;
        exit(1);
    }
    if (n <= 1) {
        std::cout << n << " 0";
        exit(0);
    }
    std::cout << "Number of edges:" << std::endl;
    std::cin >> s;
    m = strtol(s.c_str(), &endPtr, 10);
    if (*endPtr != '\0' || m < 0 || m > n * (n - 1) / 2) {
        std::cout << "invalid input" << std::endl;
        exit(1);
    }
    if (m <= 1) {
        std::cout << n << " 0";
        exit(0);
    }
}

void Graph::inputEdges() {
    char *endPtr;
    std::string s;
    for (int i = 0; i < m; i++) {
        std::cout << "Edge #" << i + 1 << ":" << std::endl;
        std::cout << "Origin:" << std::endl;
        std::cin >> s;
        int u = strtol(s.c_str(), &endPtr, 10);
        if (*endPtr != '\0') {
            std::cout << "invalid input" << std::endl;
            exit(1);
        }
        std::cout << "Destination:" << std::endl;
        std::cin >> s;
        int v = strtol(s.c_str(), &endPtr, 10);
        if (*endPtr != '\0') {
            std::cout << "invalid input" << std::endl;
            exit(1);
        }
        if (u == v || edges.count({u , v})) {
            std::cout << "invalid input" << std::endl;
            exit(1);
        }
        else {
            edges.insert({u, v});
            vertices.insert(u);
            vertices.insert(v);
            if (vertices.size() > n) {
                std::cout << "invalid input" << std::endl;
                exit(1);
            }
        }
    }
    int i = 0;
    while (vertices.size() != n) {
        vertices.insert(INT_MAX - i);
        i++;
    }
}

void Graph::makeEmptyGraph(const int& n) {
    for (int i = 1; i <= n; i++) {
        vertices.insert(i);
        map[i] = {};
    }
}

bool Graph::isAdjacent(const int &u, const int &v) const {
    return edges.find({u,v}) != edges.end();
}

void Graph::addEdge(const int &u, const int &v) {
    if (!isAdjacent(u,v)) {
        edges.insert({u,v});
        map[u].push_front(v);
    }
}

void Graph::removeEdge(const int &u, const int &v) {
    if (isAdjacent(u,v)) {
        m--;
        edges.erase({u, v});
        map[u].remove(v);
    }
}
