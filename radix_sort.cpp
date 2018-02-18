//
// Created by blazeq on 2017. 11. 8..
//

#include "catch.hpp"
#include <iostream>
#include <vector>

using namespace std;

int kth(int x, int r, int k) {
    for (int i = 0; i < k; ++i)
        x /= r;

    return x % r;
}

void sortKth(int arr[], int n, int r, int k) {
    vector<int> bucket[r];
    for (int i = 0; i < n; ++i) {
        int bucketIndex = kth(arr[i], r, k);
        bucket[bucketIndex].push_back(arr[i]);
    }

    int j = 0;
    for (int i = 0; i < r; ++i) {
        for (auto v : bucket[i]) {
            arr[j++] = v;
        }
    }
}

void radixSort(int arr[], int n, int radix, int K) {
    for (int k = 0; k < K; ++k) {
        sortKth(arr, n, radix, k);
    }
}

TEST_CASE("radix sort", "[radix sort]") {
    int arr[] = {423, 864, 162, 614, 209, 319, 910, 566, 710, 6, 28};
    int n = sizeof(arr)/sizeof(int);
    radixSort(arr, n, 10, 3);

    for (int i = 0; i < n; ++i) {
        printf("%d, ", arr[i]);
    }
    printf("\n");
}