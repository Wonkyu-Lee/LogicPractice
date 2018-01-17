//
// Created by blazeq on 2017. 12. 26..
//

#include <iostream>
#include "catch.hpp"

namespace {

using namespace std;

int printParentheses(char str[], int pairCount, int lCount, int rCount) {
    int length = lCount + rCount;
    if (length == pairCount * 2) {
        str[length] = '\0';
        cout << str << endl;
        return 1;
    }

    int count = 0;
    if (lCount > rCount) {
        str[length] = '}';
        count += printParentheses(str, pairCount, lCount, rCount + 1);
    }

    if (lCount < pairCount) {
        str[length] = '{';
        count += printParentheses(str, pairCount, lCount + 1, rCount);
    }

    return count;
}

int catalan(int n) {
    int c[n + 1]; c[0] = 1;
    for (int i = 1; i <= n; ++i) {
        c[i] = 0;
        for (int j = 0; j < i; ++j) {
            c[i] += c[j] * c[i - 1 - j];
        }
    }
    return c[n];
}

void printParentheses(int pairCount) {
    if (pairCount <= 0) return;
    char str[pairCount * 2 + 1];
    int count = printParentheses(str, pairCount, 0, 0);
    cout << "count: " << count << endl;
    cout << "catalan: " << catalan(pairCount) << endl;
}

TEST_CASE("parentheses", "[parentheses]") {
    printParentheses(5);
}

} // namespace
