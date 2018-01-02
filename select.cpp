//
// Created by blazeq on 2017. 11. 9..
//

#include <algorithm>
#include "catch.hpp"

namespace {

namespace sol1 {

int partition(int arr[], int p, int r) {
    int x = arr[r];
    int i = p - 1;
    int j = p;
    while (j < r) {
        if (arr[j] < x) {
            ++i;
            std::swap(arr[i], arr[j]);
        }
        ++j;
    }
    std::swap(arr[i + 1], arr[r]);
    return i + 1;
}

int select(int arr[], int p, int r, int i) {
    if (p > r)
        return -1;

    int q = partition(arr, p, r);
    int k = q - p;
    if (i == k) {
        return arr[q];
    } else if (i < k) {
        return select(arr, p, q - 1, i);
    } else {
        return select(arr, q + 1, r, i - k - 1);
    }
}

int select(int arr[], int n, int i) {
    if (i < 0 || n <= i)
        return -1;

    int arrCopy[n];
    std::copy(arr, arr + n, arrCopy);
    return select(arrCopy, 0, n - 1, i);
}

} // namespace sol1

TEST_CASE("Select", "[select]") {
    int arr[] = {5, 2, 9, 1, 7, 7, 3, 6, 4, 8};
    int n = sizeof(arr)/sizeof(int);

    REQUIRE(sol1::select(arr, n, 2) == 3);
    REQUIRE(sol1::select(arr, n, 6) == 7);
}

} // namespace