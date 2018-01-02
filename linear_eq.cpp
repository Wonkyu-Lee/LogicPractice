//
// Created by blazeq on 2017. 12. 27..
//

#include "catch.hpp"
#include <functional>
#include <list>

namespace {

using namespace std;

int countWays(int e[], int m, int n) {
    int dp[m + 1][n + 1];
    memset(dp, -1, sizeof(dp));

    list<int> solution;

    auto printSolution = [&]() {
        if (!solution.empty()) {
            printf("{");
            for (auto x : solution) {
                printf("%d, ", x);
            }
            printf("\b\b}\n");
        }
    };

    function<int(int, int)> cw = [&](int m, int n) {
        if (n < 0) return 0;
        if (n == 0) {
            solution.push_front(0);
            printSolution();
            solution.pop_front();
            return 1;
        }
        if (m == 1) {
            if (n % e[m - 1] == 0) {
                solution.push_front(n / e[m - 1]);
                printSolution();
                solution.pop_front();
                return 1;
            } else {
                return 0;
            }
        }

        if (dp[m][n] != -1) return dp[m][n];

        int count = 0;
        for (int i = 0; n - e[m - 1] * i >= 0; ++i) {
            solution.push_front(i);
            count += cw(m - 1, n - e[m - 1] * i);
            solution.pop_front();
        }

        return count;
    };

    return cw(m, n);
}

TEST_CASE("linear eq", "[linear eq]") {

//    SECTION("x + 2y = 5") {
//        int e[] = {1, 2};
//        int m = 2;
//        int n = 5;
//        printf("x + 2y = 5 => count: %d\n", countWays(e, m, n));
//    }

    SECTION("2x + 2y + 3z = 4") {
        int e[] = {2, 2, 3};
        int m = 3;
        int n = 4;
        printf("2x + 2y + 3z = 4 => count: %d\n", countWays(e, m, n));
    }

}

} // namespace