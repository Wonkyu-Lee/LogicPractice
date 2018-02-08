//
// Created by blazeq on 2018. 2. 7..
//

#include "catch.hpp"
#include <stack>
#include <iostream>

using namespace std;

namespace {

namespace sol1 {

void findLeftSmallers(int arr[], int n, int left[])
{
    stack<int> st;
    for (int i = 0; i < n; ++i) {
        while (!st.empty() && arr[st.top()] >= arr[i]) {
            st.pop();
        }

        left[i] = st.empty() ? -1 : st.top();
        st.push(i);
    }
}

void findRightSmallers(int arr[], int n, int right[])
{
    stack<int> st;
    for (int i = 0; i < n; ++i) {
        while (!st.empty() && arr[st.top()] > arr[i]) {
            right[st.top()] = i;
            st.pop();
        }
        st.push(i);
    }
    while (!st.empty()) {
        right[st.top()] = n;
        st.pop();
    }
}

void maxOfMinsForEachWindow(int arr[], int n, int result[])
{
    int left[n];
    int right[n];

    for (int i = 0; i < n; ++i) {
        result[i] = 0;
    }

    findLeftSmallers(arr, n, left);
    findRightSmallers(arr, n, right);

    for (int i = 0; i < n; ++i) {
        int size = right[i] - left[i] - 1;
        result[size - 1] = max(result[size - 1], arr[i]);
    }

    for (int i = n - 2; i >= 0; --i) {
        if (result[i] < result[i + 1]) {
            result[i] = result[i + 1];
        }
    }
}

} // namespace sol1

namespace sol2 {

void calcSizesOfEachMinValue(int h[], int n, int size[])
{
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

        int start = st.empty() ? 0 : st.top() + 1;
        size[j] = n - start;
    }
}

void maxOfMinsForEachWindow(int arr[], int n, int result[])
{
    for (int i = 0; i < n; ++i) {
        result[i] = 0;
    }

    int sizes[n];
    calcSizesOfEachMinValue(arr, n, sizes);

    for (int i = 0; i < n; ++i) {
        int size = sizes[i];
        cout << size << " ";
        result[size - 1] = max(result[size - 1], arr[i]);
    }
    cout << endl;

    for (int i = n - 2; i >= 0; --i) {
        if (result[i] < result[i + 1]) {
            result[i] = result[i + 1];
        }
    }
}

} // namespace sol2

} // namespace

namespace sol3 {

void maxOfMinsForEachWindow(int arr[], int n, int result[])
{
    for (int i = 0; i < n; ++i) {
        result[i] = 0;
    }

    stack<int> st;

    for (int i = 0; i < n; ++i) {
        while (!st.empty() && arr[st.top()] > arr[i]) {
            int j = st.top();
            st.pop();
            // width = [start, i), height = h[j]
            int start = st.empty() ? 0 : st.top() + 1;
            int size = i - start;
            result[size - 1] = max(result[size - 1], arr[j]);
        }

        st.push(i);
    }

    while (!st.empty()) {
        int j = st.top();
        st.pop();

        int start = st.empty() ? 0 : st.top() + 1;
        int size = n - start;
        result[size - 1] = max(result[size - 1], arr[j]);
    }

    for (int i = n - 2; i >= 0; --i) {
        if (result[i] < result[i + 1]) {
            result[i] = result[i + 1];
        }
    }
}

} // namespace sol3

TEST_CASE("Max of mins for each window", "[max of mins]") {
    int arr[] = {10, 20, 30, 50, 10, 70, 30};
    int n = sizeof(arr)/sizeof(int);
    int result[n];

    sol2::maxOfMinsForEachWindow(arr, n, result);

    for (int i = 0; i < n; ++i) {
        cout << result[i] << " ";
    }
    cout << endl;
}