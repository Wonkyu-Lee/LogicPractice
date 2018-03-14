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

    {
        int S[] = {2, 3, 5};
        print(S, 3, 5);
    }
}

} // namespace



/*
이전에 coin change 문제를 포스팅했다.

DP(Dynamic Programming)를 이용해서 문제를 풀 때 문제에 따라 테이블의 크기를 크게 줄일 수 있다.
Coin change 문제를 통해서 어떤 경우에 이렇게 공간을 줄이는게 가능한지 살펴보자.

Coin change 문제를 상기해보자.
주어진 coin들을 사용해서 거스름돈을 만들 수 있는 방법의 수를 구하는 문제이다.
문제를 재귀적으로 정의하면 다음과 같다.

coins[0..i] : 코인 배열
j: 거스름돈

Count(i, j)
= 1, if j = 0 (1)
= 0, if i < 0, j = 0 (2)
= Count(i - 1, j) + Count(i, j - coins[i]) (3)

이를 풀어쓰면 다음과 같다.
i 번째 코인까지 모두 사용해서 거스름돈 j를 만들 방법의 수
= 거스름돈이 0원일 때 1이다. 동전을 하나도 사용하지 않는 경우를 한 개로 센다.
= 거스름돈이 있는데 동전이 없을 때는 0이다.
= (i 번째 동전을 사용하지 않고 j원을 만드는 방법의 수) + (i 번째 동전을 반드시 사용해서 j원을 만드는 방법의 수)

이 형태를 테이블로 그려보면 첨부한 그림과 같다.
[i, j]를 채울 때, 이전 행인 [i - 1, j]에 [i, j - coins[i]]값을 더함을 알 수 있다.
이것은 여러 행의 정보를 유지할 필요가 없고, 단지 j값을 i번 누적하면 구할 수 있단 얘기다.

이런 코드를 위와 같은 과정 없이 바로 짜는 것은 쉽지 않다.
이런 형태의 DP 문제를 풀기 위해서는 다음과 같은 절차를 따르자.
1. 최소의 변수만 사용해서 상태를 정의한다,
2. 종료 조건을 살핀다.
3. 솔루션을 재귀적으로 정의한다.
4. 테이블을 그리고, 솔루션이 만들어지는 순서를 확인한다.
5. 유지할 정보의 차원을 더 줄일 수 있는지 확인한다.
6. 최종 테이블의 차원을 결정하고 DP로 코딩한다.
 */