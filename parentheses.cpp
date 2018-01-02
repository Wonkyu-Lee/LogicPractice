//
// Created by blazeq on 2017. 12. 26..
//

#include <iostream>
#include "catch.hpp"

namespace {

using namespace std;

int printParentheses(char str[], int pairCount, int lCount, int rCount) {
    int l = lCount + rCount;
    if (l == pairCount * 2) {
        str[l] = '\0';
        cout << str << endl;
        return 1;
    }

    int count = 0;
    if (lCount > rCount) {
        str[l] = '}';
        count += printParentheses(str, pairCount, lCount, rCount + 1);
    }

    if (lCount < pairCount) {
        str[l] = '{';
        count += printParentheses(str, pairCount, lCount + 1, rCount);
    }

    return count;
}

void printParentheses(int pairCount) {
    if (pairCount <= 0) return;
    char str[pairCount * 2 + 1];
    int count = printParentheses(str, pairCount, 0, 0);
    cout << "count: " << count << endl;
}

TEST_CASE("parentheses", "[parentheses]") {
    printParentheses(4);
}

} // namespace
