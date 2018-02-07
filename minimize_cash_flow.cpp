//
// Created by blazeq on 2018. 2. 1..
//

#include "catch.hpp"
#include <vector>
#include <cassert>
#include <queue>

namespace {

using namespace std;

using Graph = vector<vector<int>>;

void minimizeCashFlow(Graph& flow, int n) {

    int balance[n];
    memset(balance, 0, sizeof(balance));

    for (int u = 0; u < n; ++u) {
        for (int v = 0; v < n; ++v) {
            balance[u] -= flow[u][v];
            balance[v] += flow[u][v];
        }
    }

    priority_queue<int> fromQueue;
    priority_queue<int, vector<int>, greater<int>> toQueue;

    for (int v = 0; v < n; ++v) {
        if (balance[v] > 0)
            toQueue.push(v);
        else if (balance[v] < 0)
            fromQueue.push(v);
    }

    for (int u = 0; u < n; ++u) {
        for (int v = 0; v < n; ++v) {
            flow[u][v] = 0;
        }
    }

    while (!fromQueue.empty()) {
        int u = fromQueue.top();
        int v = toQueue.top();

        if (-balance[u] <= balance[v]) {
            int money = -balance[u];
            flow[u][v] = money;
            balance[u] = 0;
            balance[v] -= money;
        } else {
            int money = balance[v];
            flow[u][v] = money;
            balance[u] += money;
            balance[v] = 0;
        }

        if (balance[u] == 0)
            fromQueue.pop();

        if (balance[v] == 0)
            toQueue.pop();
    }
}

} // namespace

TEST_CASE("Minimize cash flow", "[minimize cash flow]") {
    Graph flow{4, vector<int>(4)};
    flow[0][1] = 1000;
    flow[0][2] = 2000;
    flow[1][2] = 5000;
    flow[2][3] = 4000;
    flow[3][0] = 2000;
    flow[3][1] = 1000;
    int n = 4;
    minimizeCashFlow(flow, n);

    for (int u = 0; u < n; ++u) {
        for (int v = 0; v < n; ++v) {
            if (flow[u][v] != 0) {
                printf("%d -> %d : %d\n", u, v, flow[u][v]);
            }
        }
    }
    printf("\n");
}