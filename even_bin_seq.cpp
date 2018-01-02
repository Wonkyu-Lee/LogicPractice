//
// Created by blazeq on 2017. 12. 27..
//

#include "catch.hpp"
#include <iostream>
#include <functional>

namespace {

using namespace std;

int countSeq(int n)
{
    int dp[n + 1][2 * n];
    memset(dp, -1, sizeof(dp));

    function<int(int, int)> cs = [&dp, &cs](int n, int diff) {
        if (n < abs(diff)) return 0;
        if (n == 1 && diff == 0) return 2;
        if (n == 1 && abs(diff) == 1) return 1;
        if (dp[n][n + diff] != -1) return dp[n][n + diff];
        int count = cs(n - 1, diff - 1) + 2 * cs(n - 1, diff) + cs(n - 1, diff + 1);
        return dp[n][n + diff] = count;
    };

    return cs(n, 0);
}

int countSeq2(int n) {
    int nCr = 1;
    int count = 1;
    for (int r = 1; r <= n; ++r) {
        nCr = nCr * (n - r + 1) / r;
        count += nCr * nCr;
    }
    return count;
}

TEST_CASE("even bin seq", "[even bin seq]") {
    for (int i = 1; i < 10; ++i) {
        printf("countSeq(%d) = %d, countSeq2(%d) = %d\n", i, countSeq(i), i, countSeq2(i));
    }
}

} // namespace