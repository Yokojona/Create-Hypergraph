#include <iostream>
using namespace std;
#include <vector>
#include <unordered_set>

struct hashFunc
{
    size_t operator()(const pair<int , int> &x) const{
        return x.first ^ x.second;
    }
};

int main() {
    int n, m, v, u, i;
    unordered_set<pair<int, int>, hashFunc> edges;
    unordered_set<int> vertices;
    vector<vector<int>> graph;
    char *endPtr;
    string s;
    cin >> s;
    n = strtol(s.c_str(), &endPtr, 10);
    if (*endPtr != '\0' || n < 0 || n > INT_MAX) {
        cout << "invalid input" << endl;
        exit(1);
    }
    if (n <= 1) {
        cout << n << " 0";
        exit(0);
    }
    cin >> s;
    m = strtol(s.c_str(), &endPtr, 10);
    if (*endPtr != '\0' || m < 0 || m > n * (n - 1) / 2) {
        cout << "invalid input" << endl;
        exit(1);
    }
    if (m <= 1) {
        cout << n << " 0";
        exit(0);
    }
    for (i = 0; i < m; i++) {
        cin >> s;
        u = strtol(s.c_str(), &endPtr, 10);
        if (*endPtr != '\0') {
            cout << "invalid input" << endl;
            exit(1);
        }
        cin >> s;
        v = strtol(s.c_str(), &endPtr, 10);
        if (*endPtr != '\0') {
            cout << "invalid input" << endl;
            exit(1);
        }
        if (u == v || edges.count({u , v})) {
            cout << "invalid input" << endl;
            exit(1);
        }
        else {
            edges.insert({u, v});
            vertices.insert(u);
            vertices.insert(v);
        }
    }
}