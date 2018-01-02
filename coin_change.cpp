//
// Created by blazeq on 2017. 12. 27..
//

#include "catch.hpp"
#include <functional>
#include <list>
#include <map>
#include <iostream>

namespace {

using namespace std;

int count(int S[], int m, int n) {
    if (n == 0) return 1;
    if (n < 0) return 0;
    if (m <= 0 && n > 0) return 0;
    return count(S, m - 1, n) + count(S, m, n - S[m - 1]);
}

int countMemo(int S[], int m, int n) {
    int dp[m + 1][n + 1];
    memset(dp, -1, sizeof(dp));

    function<int(int, int)> ct = [&](int i, int j) {
        if (j == 0) return 1;
        if (j < 0) return 0;
        if (i <= 0 && j > 0) return 0;

        if (dp[i][j] != -1) return dp[i][j];
        return dp[i][j] = ct(i - 1, j) + ct(i, j - S[i - 1]);
    };

    return ct(m, n);
}

int countDp(int S[], int m, int n) {
    int dp[m + 1][n + 1];
    for (int i = 0; i <= m; ++i) {
        for (int j = 0; j <= n; ++j) {
            if (j == 0) {
                dp[i][j] = 1;
            } else if (i == 0) {
                dp[i][j] = 0;
            } else {
                int excluding = dp[i - 1][j];
                int including = (j - S[i - 1] >= 0) ? dp[i][j - S[i - 1]] : 0;
                dp[i][j] = excluding + including;
            }
        }
    }

    return dp[m][n];
}

int countPrt(int S[], int m, int n) {
    map<int, int> changes;
    for (int i = 0; i < m; ++i) {
        changes[i] = 0;
    }

    auto printChanges = [&]() {
        stringstream ss;
        string separator = "";
        ss << "{";
        for (auto each : changes) {
            ss << separator << S[each.first] << ":" << each.second;
            separator = ", ";
        }
        ss << "}";
        cout << ss.str() << endl;
    };

    auto increaseChanges = [&](int change, int amount) {
        changes[change] += amount;
    };

    function<int(int, int)> recur = [&](int m, int n) {
        if (n == 0) {
            printChanges();
            return 1;
        }
        if (n < 0) return 0;
        if (m <= 0 && n > 0) return 0;

        int excluding = recur(m - 1, n);

        increaseChanges(m - 1, 1);
        int including = recur(m, n - S[m - 1]);;
        increaseChanges(m - 1, -1);

        return  excluding + including;
    };

    return recur(m, n);
}

int count2(int S[], int m, int n) {
    if (n == 0) return 1;
    int result = 0;
    for (int i = 0; i < m; ++i) {
        if (S[i] <= n) {
            result += count2(S + i, m - i, n - S[i]);
        }
    }
    return result;
}

int count2Dp(int S[], int m, int n) {
    int dp[n + 1];
    memset(dp, 0, sizeof(dp));
    dp[0] = 1;

    for (int i = 0; i < m; i++)
        for (int j = S[i]; j <= n; j++)
            dp[j] += dp[j - S[i]];

    return dp[n];
}

int count3(int S[], int m, int n) {
    if (n == 0) return 1;
    int result = 0;
    for (int size = 1; size <= m; ++size) {
        if (S[size - 1] <= n) {
            result += count3(S, size, n - S[size - 1]);
        }
    }
    return result;
}

int count3Dp(int S[], int m, int n) {
    int dp[n + 1];
    memset(dp, 0, sizeof(dp));
    dp[0] = 1;

    for (int i = 0; i < m; ++i) {
        for (int j = S[i]; j <= n; ++j) {
            dp[j] += dp[j - S[i]];
        }
    }
    return dp[n];
}

TEST_CASE("coin change", "[coin change]") {
    auto print = [](int S[], int m, int n) {
        printf("recur = %d\n", countPrt(S, m, n));
        printf("memo = %d\n", countMemo(S, m, n));
        printf("dp = %d\n", countDp(S, m, n));
        printf("sol = %d\n", count2(S, m, n));
        printf("solDp = %d\n", count2Dp(S, m, n));
        printf("count3 = %d\n", count3(S, m, n));
        printf("count3Dp = %d\n", count3Dp(S, m, n));
        printf("\n");
    };

    {
        int S[] = {2, 5, 3, 6};
        print(S, 4, 10);
    }

    {
        int S[] = {2, 2, 3};
        print(S, 3, 4);
    }

    {
        int S[] = {3, 2, 1};
        print(S, 3, 10);
    }
}

} // namespace