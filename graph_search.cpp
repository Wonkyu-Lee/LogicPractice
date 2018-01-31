//
// Created by blazeq on 2018. 1. 24..
//

#include <unordered_set>
#include <vector>
#include <queue>
#include <iostream>
#include "catch.hpp"

namespace {

using namespace std;

class Graph {
    struct Vertex {
        unordered_set<int> neighbors;
    };
    vector<Vertex> _vertices;

public:
    Graph(int vertexCount): _vertices(vertexCount) {}

    bool hasVertex(int v) const {
        return 0 <= v && v < _vertices.size();
    }

    bool hasEdge(int u, int v) const {
        if (!hasVertex(u) || !hasVertex(v)) return false;
        return _vertices[u].neighbors.find(v) != _vertices[u].neighbors.end();
    }

    bool addEdge(int u, int v) {
        if (!hasVertex(u) || !hasVertex(v)) return false;
        _vertices[u].neighbors.insert(v);
        return true;
    }

    void addEdges(const vector<pair<int, int>>& edges) {
        for (auto& edge : edges) {
            addEdge(edge.first, edge.second);
        }
    }

    void bfs(int s, function<void(int)> visit) const {
        if (!hasVertex(s)) return;
        vector<bool> visited(_vertices.size(), false);
        queue<int> q;

        visited[s] = true;
        q.push(s);

        while (!q.empty()) {
            int u = q.front(); q.pop();
            visit(u);
            for (auto v : _vertices[u].neighbors) {
                if (!visited[v]) {
                    visited[v] = true;
                    q.push(v);
                }
            }
        }
    }

    void dfs(int s, function<void(int)> visit) const {
        if (!hasVertex(s)) return;
        vector<bool> visited(_vertices.size(), false);

        function<void(int)> _dfs = [&](int u) {
            visited[u] = true;
            visit(u);
            for (auto v : _vertices[u].neighbors) {
                if (!visited[v]) {
                    _dfs(v);
                }
            }
        };

        _dfs(s);
    }


};

}

TEST_CASE("Graph search", "[graph search]") {
    Graph g(4);
    g.addEdges({{0, 1}, {0, 2}, {2, 3}, {3, 0}});

    cout << "BFS(0): ";
    g.bfs(0, [](int v){ cout << v << " "; });
    cout << endl;

    cout << "DFS(0): ";
    g.dfs(0, [](int v){ cout << v << " "; });
    cout << endl;
}