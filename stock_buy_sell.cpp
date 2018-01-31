//
// Created by blazeq on 2018. 1. 25..
//

#include "catch.hpp"

namespace {

using namespace std;

/* https://www.geeksforgeeks.org/stock-buy-sell/
 *  0   1   2   3   4   5   6
 * 100 180 260 310  40 535 695
 */

int getMaxProfit(int price[], int s, int e) {
    if (s >= e)
        return 0;

    int maxProfit = 0;

    for (int i = s; i < e; ++i) {
        for (int j = i + 1; j <= e; ++j) {
            int left = price[j] - price[i];
            int right = getMaxProfit(price, j + 1, e);
            int profit = left + right;
            if (profit > maxProfit) {
                maxProfit = profit;
            }
        }
    }

    return maxProfit;
}

int getMaxProfit(int price[], int n) {
    return getMaxProfit(price, 0, n - 1);
}

int getMaxProfitDp(int price[], int n) {
    int dp[n][n];

    for (int size = 1; size <= n; ++size) {
        for (int i = 0; i <= n - size; ++i) {
            int j = i + size - 1;
            if (i == j) {
                dp[i][j] = 0;
            } else if (i + 1 == j) {
                dp[i][j] = price[j] - price[i];
            } else {
                dp[i][j] = price[j] - price[i];
                for (int k = i + 1; k < j; ++k) {
                    dp[i][j] = max(dp[i][j], dp[i][k] + dp[k + 1][j]);
                }
            }
        }
    }

    return dp[0][n - 1];
}

} // namespace


TEST_CASE("Stock buy sell", "[stock by sell]") {
    int profit[] = {100, 180, 260, 310, 40, 535, 695};
    int n = sizeof(profit)/sizeof(int);
    REQUIRE(getMaxProfit(profit, n) == 210 + 655);
    REQUIRE(getMaxProfitDp(profit, n) == 210 + 655);
}