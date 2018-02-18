//
// Created by blazeq on 2017. 11. 9..
//

#include "catch.hpp"

namespace sol1 {

void countSort(int arr[], int n, int K) {
    int c[K];
    for (int i = 0 ; i < K; ++i) {
        c[i] = 0;
    }

    for (int i = 0; i < n; ++i) {
        ++c[arr[i]];
    }

    int k = 0;
    for (int i = 0; i < K; ++i) {
        for (int j = 0; j < c[i]; ++j) {
            arr[k++] = i;
        }
    }
}

} // namespace sol1

namespace sol2 {

void countSort(int arr[], int n, int K) {
    int c[K];
    for (int i = 0 ; i < K; ++i) {
        c[i] = 0;
    }

    for (int i = 0; i < n; ++i) {
        ++c[arr[i]];
    }

    for (int i = 1; i < K; ++i) {
        c[i] += c[i - 1];
    }

    int r[n];
    for (int i = n - 1; 0 <= i; --i) {
        int& count = c[arr[i]];
        r[count - 1] = arr[i];
        --count;
    }

    for (int i = 0; i < n; ++i) {
        arr[i] = r[i];
    }
}

} // namespace sol2

TEST_CASE("Count sort", "[count sort]") {
    int arr[] = {4, 1, 0, 2, 0, 5, 4, 3, 3, 4, 1, 5, 7};
    int n = sizeof(arr) / sizeof(int);
    sol2::countSort(arr, n, 10);

    for (int i = 0; i < n; ++i) {
        printf("%d, ", arr[i]);
    }
    printf("\n");
}