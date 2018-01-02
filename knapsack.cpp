//
// Created by blazeq on 2017. 12. 24..
//

#include "catch.hpp"
#include <unordered_map>
#include <functional>

namespace {

using namespace std;

int knapsack(int n, int w, int weights[], int values[]) {
    unordered_map<int, int> dp[n + 1];

    function<int(int, int)> maxValue = [&](int i, int j) -> int {
        //printf("dp[%d][%d]\n", i, j);

        if (dp[i].find(j) == dp[i].end()) {
            if (i == 0 || j == 0) {
                dp[i][j] = 0;
            } else if (weights[i - 1] > j) {
                dp[i][j] = maxValue(i - 1, j);
            } else {
                dp[i][j] = max(maxValue(i - 1, j), maxValue(i - 1, j - weights[i - 1]) + values[i - 1]);
            }
        }
        return dp[i][j];
    };

    return maxValue(n, w);
}

TEST_CASE("knapsack", "[knapsack]") {
    {
        int n = 3;
        int w = 4;
        int weights[] = {4, 5, 1};
        int values[] = {1, 2, 3};
        REQUIRE(knapsack(n, w, weights, values) == 3);
    }
}

} // namespace
