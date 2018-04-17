//
// Created by blazeq on 2018. 2. 13..
//

#include "catch.hpp"
#include <iostream>
#include <stack>

using namespace std;

namespace {

// 좀 특이하다.. 이건..
//bool hasDuplicateParenthesis(const string& expr) {
//    stack<char> st;
//
//    for (int i = 0; i < expr.length(); ++i) {
//        char ch = expr[i];
//
//        if (ch == ')') {
//            char top = st.top();
//            st.pop();
//            if (top == '(') {
//                return true;
//            } else {
//                while (top != '(') {
//                    top = st.top();
//                    st.pop();
//                }
//            }
//        } else {
//            st.push(ch);
//        }
//    }
//
//    return false;
//}

bool hasDuplicateParenthesis(const string& expr) {
    stack<char> st;

    for (int i = 0; i < expr.length(); ++i) {
        char ch = expr[i];

        int count = 0;
        if (ch == ')') {
            while (st.top() != '(') {
                st.pop();
                ++count;
            }
            st.pop();
            if (count == 0)
                return true;
        } else {
            st.push(ch);
        }
    }

    return false;
}

} // namespace

TEST_CASE("Duplicate parenthesis", "[duplicate parenthesis]") {
    REQUIRE(true == hasDuplicateParenthesis("((a+b)+((c+d)))"));
    REQUIRE(true == hasDuplicateParenthesis("(((a+(b)))+(c+d))"));
    REQUIRE(true == hasDuplicateParenthesis("(((a+(b))+c+d))"));
    REQUIRE(false == hasDuplicateParenthesis("((a+b)+(c+d))"));
    REQUIRE(false == hasDuplicateParenthesis("((a+(b))+(c+d))"));
}