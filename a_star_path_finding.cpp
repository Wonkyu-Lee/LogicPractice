
//

#include "catch.hpp"
#include <iostream>
#include <queue>
#include <map>
#include <list>

namespace {

using namespace std;

struct Pos {
    int r;
    int c;

    Pos(int r, int c): r(r), c(c) {}

    bool operator<(const Pos& other) const {
        return (r != other.r) ? r < other.r : c < other.c;
    }

    bool operator==(const Pos& other) const {
        return r == other.r && c == other.c;
    }

    friend ostream& operator<<(ostream& o, const Pos& p) {
        return o << "(" << p.r << ", " << p.c << ")";
    }

    double distance(const Pos& other) const {
        return diagonalDistance(other);
    }

    double manhattanDistance(const Pos& other) const {
        return abs(other.r - r) + abs(other.c - c);
    }

    double diagonalDistance(const Pos& other) const {
        return max(abs(other.r - r), abs(other.c - c));
    }

    double euclideanDistance(const Pos& other) const {
        double dr = other.r - r;
        double dc = other.c - c;
        return sqrt(dr*dr + dc*dc);
    }

    bool nil() const {
        return r == -1 && c == -1;
    }

    static const Pos& NIL() {
        static const Pos sNil(-1, -1);
        return sNil;
    }
};

class MinHeap {
    set<tuple<double, int, int>> _heap;
    map<tuple<int, int>, double> _map;
public:
    bool empty() const {
        return _heap.empty();
    }

    Pos peek() const {
        double value;
        int r;
        int c;
        tie(value, r, c) = *_heap.begin();
        return Pos(r, c);
    }

    void pop() {
        if (!_heap.empty()) {
            Pos e = peek();
            _heap.erase(_heap.begin());
            _map.erase({e.r, e.c});
        }
    }

    bool contains(const Pos& pos) const {
        return _map.find({pos.r, pos.c}) != _map.end();
    }

    bool update(const Pos& pos, double value) {
        if (!remove(pos))
            return false;

        add(pos, value);
        return true;
    }

    void addOrUpdate(const Pos& pos, double value) {
        remove(pos);
        add(pos, value);
    }

    bool remove(const Pos& pos) {
        auto it = _map.find({pos.r, pos.c});
        if (it == _map.end())
            return false;

        _heap.erase({it->second, pos.r, pos.c});
        _map.erase(it);
        return true;
    }

    bool add(const Pos& pos, double value) {
        if (contains(pos)) {
            return false;
        }

        _heap.insert({value, pos.r, pos.c});
        _map.insert({{pos.r, pos.c}, value});
        return true;
    }
};

class TileMap {
private:
    int _rows;
    int _cols;
    bool** _blocked;

public:
    TileMap(const vector<vector<int>>& stage) :_rows(stage.size()), _cols(stage[0].size()) {
        _blocked = new bool*[_rows];
        for (int i = 0; i < _rows; ++i) {
            _blocked[i] = new bool[_cols];
            for (int j = 0; j < _cols; ++j) {
                _blocked[i][j] = (stage[i][j] == 0);
            }
        }
    }

    ~TileMap() {
        for (int i = 0; i < _rows; ++i)
            delete _blocked[i];
    }

    list<Pos> getShortedPath(const Pos& src, const Pos& dst) {
        list<Pos> emptyPath;
        if (!valid(src) || !valid(dst))
            return emptyPath;

        if (blocked(src) || blocked(dst))
            return emptyPath;

        auto heuristic = [&](const Pos& p) {
            return p.diagonalDistance(dst);
        };

        static const double INF = numeric_limits<double>::infinity();
        struct TileInfo {
            double g{INF};
            double h{INF};
            double f() const { return g + h; }
            Pos prev{Pos::NIL()};
        };

        TileInfo infos[_rows][_cols];
        auto info = [&infos](const Pos& p) -> TileInfo& {
            return infos[p.r][p.c];
        };

        for (int r = 0; r < _rows; ++r) {
            for (int c = 0; c < _cols; ++c) {
                Pos p(r, c);
                TileInfo& tileInfo = info(p);
                tileInfo.h =  heuristic(p);
            }
        }

        MinHeap open;
        set<Pos> closed;

        TileInfo& srcInfo = info(src);
        srcInfo.g = 0;
        open.add(src, srcInfo.f());

        bool found = false;
        while (!open.empty()) {
            Pos u = open.peek();
            open.pop();
            closed.insert(u);

            if (u == dst) {
                found = true;
                break;
            }

            TileInfo& uInfo = info(u);
            vector<Pos> adjs = getAdjs(u);
            for (auto& v : adjs) {
                if (closed.find(v) != closed.end() || blocked(v))
                    continue;

                TileInfo& vInfo = info(v);
                double g = uInfo.g + u.distance(v);
                if (g < vInfo.g) {
                    vInfo.g = g;
                    open.addOrUpdate(v, vInfo.f());
                    vInfo.prev = u;
                }
            }
        }

        if (!found) {
            return emptyPath;
        }

        // build path
        list<Pos> path;
        Pos current = dst;
        while (!current.nil()) {
            path.push_front(current);
            current = infos[current.r][current.c].prev;
        }

        return path;
    }

    bool valid(const Pos& p) const {
        return (0 <= p.r && p.r < _rows) && (0 <= p.c && p.c < _cols);
    }

    bool blocked(const Pos& p) const {
        return _blocked[p.r][p.c];
    }

    vector<Pos> getAdjs(const Pos& p) const {
        vector<Pos> r;
        for (int i = -1; i <= 1; ++i) {
            for (int j = -1; j <= 1; ++j) {
                if (i == 0 && j == 0)
                    continue; // except self

                Pos q(p.r + i, p.c + j);
                if (!valid(q))
                    continue;

                r.push_back(q);
            }
        }
        return r;
    }

    void printStage() const {
        for (int r = 0; r < _rows; ++r) {
            for (int c = 0; c < _cols; ++c) {
                cout << (_blocked[r][c] ? "B" : " ");
            }
            cout << endl;
        }
    }

    void printPath(const list<Pos>& path) const {
        if (path.empty()) {
            printStage();
            return;
        }

        set<Pos> nodes(path.begin(), path.end());
        Pos start = path.front();
        Pos goal = path.back();

        for (int r = 0; r < _rows; ++r) {
            for (int c = 0; c < _cols; ++c) {
                Pos p(r, c);
                bool onPath = nodes.find(p) != nodes.end();

                char ch = ' ';
                if (_blocked[r][c]) {
                    ch = 'B';
                } else if (p == start) {
                    ch = '@';
                } else if (p == goal) {
                    ch = '@';
                } else if (onPath) {
                    ch = '+';
                }

                cout << ch;
            }
            cout << endl;
        }
    }
};

}

TEST_CASE("A* path finding", "[a star]") {
    SECTION("Test MinHeap") {
        MinHeap heap;

        // new
        heap.addOrUpdate({0, 1}, 1);
        heap.addOrUpdate({1, 2}, 2);
        heap.addOrUpdate({2, 1}, 3);
        heap.addOrUpdate({0, 0}, 4);
        heap.addOrUpdate({3, 0}, 2);

        // modify
        heap.addOrUpdate({2, 1}, 4);

        cout << "Test MinHeap" << endl;
        while (!heap.empty()) {
            Pos p = heap.peek();
            heap.pop();
            cout << p << endl;
        }
    }

    SECTION("Test A* path finding") {
        // 0: blocked
        vector<vector<int>> stage = {
                { 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 },
                { 1, 1, 1, 0, 1, 1, 1, 0, 1, 1 },
                { 1, 1, 1, 0, 1, 1, 0, 1, 0, 1 },
                { 0, 0, 1, 0, 1, 0, 0, 0, 0, 1 },
                { 1, 1, 1, 0, 1, 1, 1, 0, 1, 0 },
                { 1, 0, 1, 1, 1, 1, 0, 1, 0, 0 },
                { 1, 0, 0, 0, 0, 1, 0, 0, 0, 1 },
                { 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 },
                { 1, 1, 1, 0, 0, 0, 1, 0, 0, 1 }
        };

        TileMap tileMap(stage);
        auto path = tileMap.getShortedPath({8, 0}, {0, 0});

        cout << "Path: ";
        for (auto& p : path) {
            cout << p << " ";
        }
        cout << endl;

        tileMap.printPath(path);
    }
}