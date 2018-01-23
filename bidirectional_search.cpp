//
// Created by blazeq on 2017. 11. 2..
//

#include "catch.hpp"
#include <iostream>
#include <unordered_map>
#include <set>
#include <list>

using namespace std;

class Graph {
private:
    struct Vertex {
        set<int> adjs;
    };

    unordered_map<int, shared_ptr<Vertex>> vertices;
    size_t createdCount = 0;

public:
    int addVertex() {
        size_t newId = createdCount++;
        vertices[newId] = make_shared<Vertex>();
        return newId;
    }

    bool hasVertex(int u) const {
        return vertices.find(u) != vertices.end();
    }

    bool addEdge(int u, int v) {
        if (vertices.find(u) == vertices.end()) {
            return false;
        }

        if (vertices.find(v) == vertices.end()) {
            return false;
        }

        vertices[u]->adjs.insert(v);
        vertices[v]->adjs.insert(u);
        return true;
    }

    using Range = pair<set<int>::const_iterator, set<int>::const_iterator>;
    bool getAdjs(int u, Range& range) const {
        auto found = vertices.find(u);
        if (found == vertices.end()) {
            return false;
        }

        range = make_pair(found->second->adjs.begin(), found->second->adjs.end());
        return true;
    }
};

class BfsData {
private:
    unordered_map<int, bool> _visited;
    unordered_map<int, int> _prev;
    list<int> _queue;

public:
    BfsData(int u) {
        _visited[u] = true;
        _prev[u] = -1;
        _queue.push_back(u);
    }

    int pop() {
        if (_queue.empty())
            return -1;

        int front = _queue.front();
        _queue.pop_front();
        return front;
    }

    void push(int u) {
        _queue.push_back(u);
    }

    bool finished() const {
        return _queue.empty();
    }

    bool visited(int u) const {
        auto found = _visited.find(u);
        if (found == _visited.end())
            return false;
        return found->second;
    }

    int prev(int u) const {
        auto found = _prev.find(u);
        if (found == _prev.end())
            return -1;
        return found->second;
    }

    void setPrev(int u, int p) {
        _prev[u] = p;
    }

    void setVisited(int u) {
        _visited[u] = true;
    }

    int size() const {
        return _queue.size();
    }
};

int searchLevel(const Graph& g, BfsData& bfsFrom, BfsData& bfsTo) {
    for (int i = 0; i < bfsFrom.size(); ++i) {
        int u = bfsFrom.pop();

        if (bfsTo.visited(u)) {
            return u;
        }

        Graph::Range adjs;
        if (g.getAdjs(u, adjs)) {
            for (auto it = adjs.first; it != adjs.second; ++it) {
                int v = *it;
                if (!bfsFrom.visited(v)) {
                    bfsFrom.setVisited(v);
                    bfsFrom.setPrev(v, u);
                    bfsFrom.push(v);
                }
            }
        }
    }
    return -1;
}

list<int> getShortestPath(const Graph& g, int from, int to) {
    unordered_map<int, bool> visited;
    list<int> path;

    BfsData bfsFrom(from);
    BfsData bfsTo(to);

    while (!bfsFrom.finished() && !bfsTo.finished()) {
        int collision = searchLevel(g, bfsFrom, bfsTo);
        if (collision == -1) {
            collision = searchLevel(g, bfsTo, bfsFrom);
        }

        if (collision != -1) {
            path.push_back(collision);
            int cur = bfsFrom.prev(collision);
            while (cur != -1) {
                path.push_front(cur);
                cur = bfsFrom.prev(cur);
            }
            cur = bfsTo.prev(collision);
            while (cur != -1) {
                path.push_back(cur);
                cur = bfsTo.prev(cur);
            }

            return path;
        }
    }

    return path;
}

TEST_CASE("Bidirectional search", "[bidirectional search]") {

    SECTION("Test graph")
    {
        Graph g;
        int v[5];
        for (int i = 0; i < 5; ++i) {
            v[i] = g.addVertex();
        }

        g.addEdge(v[1], v[2]);
        g.addEdge(v[1], v[3]);
        g.addEdge(v[1], v[4]);

        Graph::Range adjs;
        printf("vertex %d's adj: ", v[1]);
        if (g.getAdjs(v[1], adjs)) {
            auto it = adjs.first;
            for (; it != adjs.second; ++it) {
                printf("%d, ", *it);
            }
            printf("\n");
        }
    }

    SECTION("Search the shortest pat") {
        Graph g;
        for (int i = 0; i < 10; ++i) {
            g.addVertex();
        }

        g.addEdge(0, 1);
        g.addEdge(0, 3);
        g.addEdge(2, 7);
        g.addEdge(3, 2);
        g.addEdge(3, 4);
        g.addEdge(3, 5);
        g.addEdge(3, 8);
        g.addEdge(6, 9);
        g.addEdge(8, 9);

        int from = 0;
        int to = 9;
        printf("path from %d to %d: ", from, to);
        auto path = getShortestPath(g, from, to);
        for (auto v : path) {
            printf("%d, ", v);
        }
        printf("\n");
    }

}