//
// Created by blazeq on 2018. 2. 12..
//

#include "catch.hpp"
#include <iostream>
#include <stack>

using namespace std;

// https://www.geeksforgeeks.org/minimum-number-of-bracket-reversals-needed-to-make-an-expression-balanced/
namespace {

int minReversals(const string& parentheses) {
    if (parentheses.length() % 2 == 1)
        return -1;

    stack<char> st;
    int count = 0;
    for (char c : parentheses) {
        if (c == '}') {
            if (st.empty()) {
                count++;
                st.push(c);
            } else {
                st.pop();
            }
        } else if (c == '{') {
            st.push(c);
        }
    }

    count += st.size() / 2;
    return count;
}

int minReversals2(const string& parentheses) {
    if (parentheses.length() % 2 == 1)
        return -1;

    int opens = 0;
    int count = 0;
    for (char c : parentheses) {
        if (c == '}') {
            if (opens == 0) {
                count++;
                opens++;
            } else {
                opens--;
            }
        } else if (c == '{') {
            opens++;
        }
    }

    count += opens / 2;
    return count;
}

} // namespace

TEST_CASE("Minimum number of bracket reversals", "[min bracket reversals]") {
    REQUIRE( 2 == minReversals2("}{"));
    REQUIRE(-1 == minReversals2("{{{"));
    REQUIRE( 2 == minReversals2("{{{{"));
    REQUIRE( 1 == minReversals2("{{{{}}"));

    REQUIRE( 3 == minReversals2("}}}{"));
    REQUIRE( 3 == minReversals2("}{{{"));
    REQUIRE( 2 == minReversals2("}}{{"));
}