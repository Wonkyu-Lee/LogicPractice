//
// Created by blazeq on 2017. 12. 22..
//

#include <iostream>
#include <unordered_set>
#include <vector>
#include "catch.hpp"

namespace {

using namespace std;
using Set = unordered_set<int>;

bool sumExists(Set s, int n, Set& r) {
    if (n < 0) return false;

    if (n == 0) {
        stringstream ss;
        for (auto e : r) {
            ss << e << " ";
        }
        cout << ss.str() << endl;
        return true;
    }

    Set v = s;
    for (auto e : s) {
        v.erase(e);
        r.insert(e);
        if (sumExists(v, n - e, r)) {
            return true;
        }
        r.erase(e);
        v.insert(e);
    }

    return false;
}

bool sumExists(Set s, int n) {
    Set r;
    return sumExists(s, n, r);
}




bool sumExists2(const vector<int>& s, int m, int n) {
    if (n < 0) return false;
    if (n == 0) return true;
    if (m == 0) return false;

    return sumExists2(s, m - 1, n) || sumExists2(s, m - 1, n - s[m - 1]);
}

bool sumExists3(const vector<int>& s, int m, int n) {
    bool dp[m + 1][n + 1];
    for (int i = 0; i <= m; ++i) {
        for (int j = 0; j <= n; ++j) {
            if (j == 0) {
                dp[i][j] = true;
            } else if (i == 0) {
                dp[i][j] = false;
            } else {
                dp[i][j] = dp[m - 1][n] || dp[m - 1][n - s[m - 1]];
            }
        }
    }
    return dp[m][n];
}

TEST_CASE("sum exists", "[sum exists]") {
    REQUIRE(sumExists({3, 34, 4, 12, 5, 2}, 9));
    REQUIRE(sumExists({3, 34, 4, 12, 5, 2}, 6));
    REQUIRE(sumExists({3, 34, 4, 12, 5, 2}, 24));

    REQUIRE(sumExists2({3, 34, 4, 12, 5, 2}, 6, 9));
    REQUIRE(sumExists2({3, 34, 4, 12, 5, 2}, 6, 6));
    REQUIRE(sumExists2({3, 34, 4, 12, 5, 2}, 6, 24));

    REQUIRE(sumExists3({3, 34, 4, 12, 5, 2}, 6, 9));
    REQUIRE(sumExists3({3, 34, 4, 12, 5, 2}, 6, 6));
    REQUIRE(sumExists3({3, 34, 4, 12, 5, 2}, 6, 24));
}

} // namespace