//
// Created by blazeq on 2018. 1. 17..
//

#include "catch.hpp"
#include <iostream>
#include <unordered_set>

namespace {

using namespace std;

class Graph {
private:
    struct Vertex {
        unordered_set<int> adj;
    };

    vector<Vertex> _vertices;

public:
    Graph(int vertexCount): _vertices(vertexCount) {}

    void addEdges(const vector<pair<int, int>>& edges) {
        for (auto& edge : edges) {
            _vertices[edge.first].adj.insert(edge.second);
            _vertices[edge.second].adj.insert(edge.first);
        }
    }

    int getVertexCount() const {
        return _vertices.size();
    }

    const unordered_set<int>& getAdjacency(int v) const {
        return _vertices[v].adj;
    }

    bool hasEdge(int u, int v) const {
        if (!hasVertex(u) || !hasVertex(v))
            return false;

        return _vertices[u].adj.find(v) != _vertices[u].adj.end();
    }

    bool hasVertex(int v) const {
        return 0 <= v && v < _vertices.size();
    }
};

class GraphColoring {
public:
    GraphColoring(const Graph& graph, int colorCount)
            : _graph(graph)
            , _colorCount(colorCount)
            , _vertexColors(_graph.getVertexCount(), -1) {

        if (_graph.getVertexCount() == 0 || _colorCount == 0)
            _possible = false;

        _possible = paint(0, 0);
    }

    bool possible() const {
        return _possible;
    }

    const vector<int>& getVertexColors() const {
        return _vertexColors;
    }

private:
    bool paint(int i, int color) {
        if (!valid(i, color)) {
            return false;
        }

        _vertexColors[i] = color;
        if (i == _graph.getVertexCount() - 1) {
            return true;
        }

        for (int c = 0; c < _colorCount; ++c) {
            if (paint(i + 1, c))
                return true;
        }

        return false;
    }

    bool valid(int i, int color) {
        for (int j = 0; j < i; ++j) {
            if (_graph.hasEdge(i, j)) {
                if (_vertexColors[j] == color)
                    return false;
            }
        }
        return true;
    }

    const Graph& _graph;
    vector<int> _vertexColors;
    int _colorCount;
    bool _possible;
};


// 가정: 모두다 connected component라고 가정한 건데, 구려.
class GraphColoring2 {
public:
    GraphColoring2(const Graph& graph, int colorCount)
            : _graph(graph)
            , _colorCount(colorCount)
            , _vertexColors(_graph.getVertexCount(), -1) {

        if (_graph.getVertexCount() == 0 || _colorCount == 0)
            _possible = false;

        _possible = paint(0, 0, 0);
    }

    bool possible() const {
        return _possible;
    }

    const vector<int>& getVertexColors() const {
        return _vertexColors;
    }

private:
    bool valid(int i, int color) const {
        if (_vertexColors[i] != -1) {
            return false;
        }

        auto& adjs = _graph.getAdjacency(i);
        for (auto j : adjs) {
            if (_vertexColors[j] == color) {
                return false;
            }
        }

        return true;
    }

    bool paint(int i, int color, int colored) {
        if (!valid(i, color)) {
            return false;
        }

        _vertexColors[i] = color;
        ++colored;

        if (colored == _graph.getVertexCount()) {
            return true;
        }

        auto& adjs = _graph.getAdjacency(i);
        for (auto j : adjs) {
            for (int c = 0; c < _colorCount; ++c) {
                if (c == color)
                    continue;

                if (paint(j, c, colored)) {
                    return true;
                }
            }
        }

        _vertexColors[i] = -1;

        return false;
    }

    const Graph& _graph;
    vector<int> _vertexColors;
    int _colorCount;
    bool _possible;
};

}

TEST_CASE("Graph coloring", "[graph coloring]") {

    Graph g(6);
    g.addEdges({{0, 1}, {0, 2}, {0, 3}, {0, 5}, {1, 4}, {1, 5}, {2, 5}, {3, 4}, {3, 5}, {4, 5}});

    GraphColoring2 coloring(g, 3);
    printf("Possible? %s\n", coloring.possible() ? "yes" : "no");

    if (coloring.possible()) {
        printf("Colors: ");
        int i = 0;
        for (auto color : coloring.getVertexColors()) {
            printf("(v:%d, color:%d) ", i++, color);
        }
    }
}
