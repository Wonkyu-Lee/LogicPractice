//
// Created by blazeq on 2018. 2. 7..
//

#include "catch.hpp"
#include <vector>
#include <iostream>
#include <stack>
#include <set>
#include <functional>

using namespace std;

namespace {

class Graph {
    struct Vertex {
        set<int> adjs;
    };
    vector<Vertex> vertices;

public:
    Graph(int n): vertices(n) {}

    int size() const { return vertices.size(); }

    vector<int> adjs(int u) const {
        return vector<int>(vertices[u].adjs.begin(), vertices[u].adjs.end());
    }

    void addEdge(int u, int v) {
        vertices[u].adjs.insert(v);
    }
};

void dfs(const Graph& g, int u, function<void(int)> visit) {
    vector<bool> visited(g.size(), false);
    stack<int> st;

    visited[u] = true;
    st.push(u);
    visit(u);

    while (true) {
        bool deeper = false;
        for (int v : g.adjs(u)) {
            if (!visited[v]) {
                visited[v] = true;
                st.push(v);
                visit(v);
                u = v;
                deeper = true;
                break;
            }
        }
        if (deeper == false) {
            if (st.empty()) {
                break;
            } else {
                u = st.top();
                st.pop();
            }
        }
    }
}

} // namespace

TEST_CASE("Iterative DFS", "[iterative_dfs]") {
    Graph g(5);
    g.addEdge(0, 2);
    g.addEdge(0, 3);
    g.addEdge(1, 0);
    g.addEdge(2, 1);
    g.addEdge(3, 4);
    g.addEdge(4, 0);

    dfs(g, 0, [](int v) {
        cout << v << " ";
    });
    cout << endl;
}