//
// Created by blazeq on 2018. 2. 8..
//

#include "catch.hpp"
#include <iostream>
#include <stack>

using namespace std;

namespace sol1 {

int largestRectangularAreaInHistogram(int h[], int n) {
    stack<int> st;
    int maxArea = 0;

    for (int i = 0 ; i < n; ++i) {
        while (!st.empty() && h[st.top()] > h[i]) {
            int j = st.top();
            st.pop();
            // width = [start, i), height = h[j]
            int start = st.empty() ? 0 : st.top() + 1;
            int area = (i - start) * h[j];
            maxArea = max(maxArea, area);
        }

        st.push(i);
    }

    while (!st.empty()) {
        int j = st.top();
        st.pop();
        // width = [start, n), height = h[j]
        int start = st.empty() ? 0 : st.top() + 1;
        int area = (n - start) * h[j];
        maxArea = max(maxArea, area);
    }

    return maxArea;
}

} // namespace sol1

namespace sol2 {

void calcSizesOfEachMinValue(int h[], int n, int size[]) {
    stack<int> st;

    for (int i = 0; i < n; ++i) {
        while (!st.empty() && h[st.top()] > h[i]) {
            int j = st.top();
            st.pop();
            // width = [start, i), height = h[j]
            int start = st.empty() ? 0 : st.top() + 1;
            size[j] = i - start;
        }

        st.push(i);
    }

    while (!st.empty()) {
        int j = st.top();
        st.pop();
        // width = [start, n), height = h[j]
        int start = st.empty() ? 0 : st.top() + 1;
        size[j] = n - start;
    }
}

int largestRectangularAreaInHistogram(int h[], int n) {
    int size[n];
    calcSizesOfEachMinValue(h, n, size);

    int maxArea = 0;
    for (int i = 0; i < n; ++i) {
        maxArea = max(maxArea, size[i] * h[i]);
    }

    return maxArea;
}

} // namespace sol2

TEST_CASE("Largest rectangular area in histogram", "[largest rect area]") {
    int h[] = {6, 2, 5, 4, 5, 1, 6};
    int n = sizeof(h) / sizeof(int);

    REQUIRE(sol1::largestRectangularAreaInHistogram(h, n) == 12);
    REQUIRE(sol2::largestRectangularAreaInHistogram(h, n) == 12);
}