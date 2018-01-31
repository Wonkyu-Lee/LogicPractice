//
// Created by blazeq on 2017. 12. 21..
//

#include "catch.hpp"
#include <iostream>
#include <unordered_map>
#include <list>

namespace {

using namespace std;

int minEditDistance(const string& str1, const string& str2) {
    int m = str1.length();
    int n = str2.length();
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

int minEditDistancePrt(const string& str1, const string& str2) {
    int m = str1.length();
    int n = str2.length();
    int dp[m + 1][n + 1];
    char edit[m + 1][n + 1];

    edit[0][0] = 'n';
    dp[0][0] = 0;

    for (int i = 1; i <= m; ++i) {
        dp[i][0] = i;
        edit[i][0] = 'd';
    }

    for (int i = 1; i <= n; ++i) {
        dp[0][i] = i;
        edit[0][i] = 'i';
    }

    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (str1[i - 1] == str2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
                edit[i][j] = 'm';
            } else {
                dp[i][j] = 1 + dp[i - 1][j - 1];
                edit[i][j] = 's';

                unordered_map<char, int> cost;
                cost['s'] = 1 + dp[i - 1][j - 1];
                cost['d'] = 1 + dp[i - 1][j];
                cost['i'] = 1 + dp[i][j - 1];

                dp[i][j] = numeric_limits<int>::max();
                for (auto& each : cost) {
                    if(dp[i][j] > each.second) {
                        dp[i][j] = each.second;
                        edit[i][j] = each.first;
                    }
                }
            }
        }
    }

    list<char> path;
    function<void(int, int)> makePath = [&](int i, int j) {
        char e = edit[i][j];
        switch (e) {
            case 'm':
            case 's':
                makePath(i - 1, j - 1);
                path.push_front(e);
                break;
            case 'd':
                makePath(i - 1, j);
                path.push_front(e);
                break;
            case 'i':
                makePath(i, j - 1);
                path.push_front(e);
                break;
            default:
                break;
        }
    };

    cout << "s1: " << str1 << endl;
    cout << "s2: " << str2 << endl;
    cout << "path: ";
    makePath(m, n);
    for (auto c : path) {
        cout << c << " ";
    }
    cout << endl;


    return dp[m][n];
}

// https://ide.geeksforgeeks.org/nW0uaUgW0U
bool editDistanceEqualsOne(const string& str1, const string& str2, int m, int n) {
    if (abs(m - n) > 1)
        return false;

    if (m == 0)
        return n <= 1;

    if (n == 0)
        return m <= 0;

    if (str1[m - 1] == str2[n - 1]) {
        return editDistanceEqualsOne(str1, str2, m - 1, n - 1);
    } else {
        string subStr1 = str1.substr(0, m - 1);
        string subStr2 = str2.substr(0, n - 1);

        if (str1.substr(0, m - 1) == str2.substr(0, n))
            return true;

        if (str1.substr(0, m) == str2.substr(0, n - 1))
            return true;

        if (str1.substr(0, m - 1) == str2.substr(0, n - 1))
            return true;

        return false;
    }
}

bool editDistanceEqualsOne(const string& str1, const string& str2) {
    return editDistanceEqualsOne(str1, str2, str1.length(), str2.length());
}

TEST_CASE("edit distance", "[edit distance]")
{
    REQUIRE(minEditDistancePrt("cat", "crt") == 1);
    REQUIRE(minEditDistancePrt("geek", "gesek") == 1);
    REQUIRE(minEditDistancePrt("saturday", "sunday") == 3);

    REQUIRE(editDistanceEqualsOne("cat", "crt"));
    REQUIRE(editDistanceEqualsOne("geek", "gesek"));
    REQUIRE(editDistanceEqualsOne("saturday", "sunday") == false);
}

} // namespace