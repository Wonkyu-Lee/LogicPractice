//
// Created by blazeq on 2018. 2. 7..
//

#include "catch.hpp"
#include <stack>
#include <iostream>

namespace {

using namespace std;

void findLeftSmallers(int arr[], int n, int left[]) {
    stack<int> st;
    left[0] = -1;
    st.push(0);
    for (int i = 1; i < n; ++i) {
        while (!st.empty() && arr[st.top()] >= arr[i]) {
            st.pop();
        }

        left[i] = st.empty() ? -1 : st.top();
        st.push(i);
    }
}

void findRightSmallers(int arr[], int n, int right[]) {
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

void maxOfMinsForEachWindow(int arr[], int n, int result[]) {
    int left[n];
    int right[n];

    for (int i = 0; i < n; ++i) {
        result[i] = 0;
    }

    findLeftSmallers(arr, n, left);
    for (int i = 0; i < n; ++i) {
        cout << left[i] << " ";
    }
    cout << endl;


    findRightSmallers(arr, n , right);
    for (int i = 0; i < n; ++i) {
        cout << right[i] << " ";
    }
    cout << endl;

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

} // namespace

TEST_CASE("Max of mins for each window", "[max of mins]") {
    int arr[] = {10, 20, 30, 50, 10, 70, 30};
    int n = sizeof(arr)/sizeof(int);
    int result[n];

    maxOfMinsForEachWindow(arr, n, result);

    for (int i = 0; i < n; ++i) {
        cout << result[i] << " ";
    }
    cout << endl;
}