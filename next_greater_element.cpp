//
// Created by blazeq on 2018. 2. 6..
//

#include "catch.hpp"
#include <iostream>
#include <stack>

namespace {

using namespace std;

void findNextGreaterElement(int array[], int n, int result[]) {
    stack<int> st;
    for (int i = 0; i < n; ++i) {
        while (!st.empty() && array[st.top()] < array[i]) {
            result[st.top()] = i;
            st.pop();
        }

        st.push(i);
    }

    while (!st.empty()) {
        result[st.top()] = n;
        st.pop();
    }
}

} // namespace

TEST_CASE("Next greater element", "[next greater element]") {
    int array[] = {4, 5, 7, 5, 2, 25};
    int n = sizeof(array) / sizeof(int);

    int result[n];
    findNextGreaterElement(array, n, result);

    for (int i = 0; i < n; ++i) {
        printf("NGE of %d = %d, ", array[i], (result[i] == n ? -1 : array[result[i]]));
    }
    cout << endl;
}