//
// Created by yokoj on 12/05/2024.
//
#include "Graph.h"

void Graph::inputGraph() {
    inputGraphSize();
    inputEdges();
    for (auto v : vertices) {
        for (auto e : edges) {
            if (e.first == v) {
                adjacencyList[v].push_front(e.second);
            }
        }
        if (adjacencyList.find(v) == adjacencyList.end())
            adjacencyList[v] = {};
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
    /*if (n <= 1) {
        std::cout << n << " 0";
        exit(0);
    }*/
    std::cout << "Number of edges:" << std::endl;
    std::cin >> s;
    m = strtol(s.c_str(), &endPtr, 10);
    if (*endPtr != '\0' || m < 0 || m > n * (n - 1) / 2) {
        std::cout << "invalid input" << std::endl;
        exit(1);
    }
    /*if (m <= 1) {
        std::cout << n << " 0";
        exit(0);
    }*/
}

void Graph::inputEdges() {
    char *endPtr;
    std::string s;
    for (auto i = 0; i < m; i++) {
        std::cout << "Edge #" << i + 1 << ":" << std::endl;
        std::cin >> s;
        auto u = strtol(s.c_str(), &endPtr, 10);
        if (*endPtr != '\0') {
            std::cout << "invalid input" << std::endl;
            exit(1);
        }
        std::cin >> s;
        auto v = strtol(s.c_str(), &endPtr, 10);
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
    auto i = 1;
    while (vertices.size() != n) {
        if (vertices.find(i) == vertices.end()) {
            vertices.insert(i);
        }
        i++;
    }
}

bool Graph::isAdjacent(const int &u, const int &v) const {
    return edges.find({u,v}) != edges.end();
}

void Graph::addEdge(const int &u, const int &v) {
    if (u != v && !isAdjacent(u,v)) {
        m++;
        edges.insert({u,v});
        adjacencyList[u].push_front(v);
    }
}

void Graph::removeEdge(const int &u, const int &v) {
    if (isAdjacent(u,v)) {
        m--;
        edges.erase({u, v});
        adjacencyList[u].remove(v);
    }
}

void Graph::transpose() {
    Graph g = *this;
    edges.clear();
    adjacencyList.clear();
    for (auto e : g.edges) {
        addEdge(e.second, e.first);
    }
    for (auto v : vertices) {
        if (adjacencyList.find(v) == adjacencyList.end())
            adjacencyList[v] = {};
    }
}

Graph Graph::getHyperGraph() {
    auto gT = *this;
    gT.transpose();
    std::unordered_map<int,bool> visited;
    for (const auto& v : adjacencyList) {
        visited[v.first] = false;
    }
    std::list<int> finishOrder;
    while (finishOrder.size() < n) {
        auto itr = std::find_if(visited.begin(),
                                visited.end(),[](std::pair<int,bool> v) {return !v.second;});
        DFS(itr->first, visited, finishOrder);
    }
    finishOrder.reverse();
    for (const auto& v : adjacencyList) {
        visited[v.first] = false;
    }
    std::unordered_map<int, std::list<int>> stronglyConnectedComponents;
    auto size = 0;
    for (auto v : finishOrder) {
        if (!visited[v]) {
            gT.DFS(v, visited, stronglyConnectedComponents[size++]);
        }
    }
    Graph hyperGraph(size);
    for (const auto& component1 : stronglyConnectedComponents) {
        for (const auto& component2 : stronglyConnectedComponents) {
            if (component1 != component2) {
                for (const auto& v1 : component1.second) {
                    for (const auto& v2 : component2.second) {
                        if (isAdjacent(v1,v2)) {
                            hyperGraph.addEdge(component1.first, component2.first);
                        }
                        if (isAdjacent(v2,v1)) {
                            hyperGraph.addEdge(component2.first, component1.first);
                        }
                    }
                }
            }
        }
    }
    return hyperGraph;
}

void Graph::DFS(const int &startNode, std::unordered_map<int, bool>& visited, std::list<int>& finishOrder) {
    std::stack<int> stack;
    stack.push(startNode);
    while (!stack.empty()) {
        int curr = stack.top();
        visited[curr] = true;
        auto finished = true;
        std::list<int> neighbours = getAdjList(curr);
        for (auto neighbour : neighbours) {
            if (!visited[neighbour]) {
                stack.push(neighbour);
                finished = false;
                break;
            }
        }
        if (finished) {
            finishOrder.push_back(curr);
            stack.pop();
        }
    }
}

Graph::Graph(const int& n) : n(n) {
    for (auto i = 0; i < n; i++) {
        vertices.insert(i);
        adjacencyList[i] = {};
    }
}

void Graph::printSize() const {
    std::cout << n << " " << m;
}
