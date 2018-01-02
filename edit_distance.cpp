//
// Created by blazeq on 2017. 12. 21..
//

#include "catch.hpp"
#include <iostream>

namespace {

using namespace std;

int editDistance(const string& str1, const string& str2, int m, int n) {
    int dp[m + 1][n + 1];
    dp[0][0] = 0;
    for (int i = 1; i <= m; ++i) dp[i][0] = i;
    for (int i = 1; i <= n; ++i) dp[0][i] = i;

    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (str1[i - 1] == str2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            } else {
                dp[i][j] = 1 + min({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]});
            }
        }
    }
    return dp[m][n];
}

int editDistance(const string& str1, const string& str2) {
    return editDistance(str1, str2, str1.length(), str2.length());
}

TEST_CASE("edit distance", "[edit distance]")
{
    REQUIRE(editDistance("cat", "crt") == 1);
    REQUIRE(editDistance("geek", "gesek") == 1);
    REQUIRE(editDistance("saturday", "sunday") == 3);
}

} // namespace