//
// Created by blazeq on 2018. 2. 7..
//

#include "catch.hpp"
#include <iostream>
#include <stack>

namespace {

using namespace std;

void calcSpan(int price[], int n, int span[]) {
    stack<int> st;
    for (int i = 0; i < n; ++i) {
        while (!st.empty() && price[st.top()] <= price[i])
            st.pop();
        span[i] = st.empty() ? i + 1 : i - st.top();
        st.push(i);
    }
}

} // namespace

TEST_CASE("Stock span", "[stock span]") {
    int price[] = {100, 80, 60, 70, 60, 75, 85};
    int n = sizeof(price) / sizeof(int);

    int span[n];
    calcSpan(price, n, span);

    for (int i = 0; i < n; ++i) {
        cout << span[i] << " ";
    }
    cout << endl;
}