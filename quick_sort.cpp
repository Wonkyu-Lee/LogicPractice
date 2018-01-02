//
// Created by blazeq on 2017. 11. 9..
//

#include "catch.hpp"

namespace {

namespace sol1 {

int partition(int arr[], int p, int r) {
    int i = p - 1;
    int j = p;
    int x = arr[r];

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

void quickSort(int arr[], int p, int r) {
    if (p > r) return;
    int q = partition(arr, p, r);
    quickSort(arr, p, q - 1);
    quickSort(arr, q + 1, r);
}

void quickSort(int arr[], int n) {
    quickSort(arr, 0, n - 1);
}

} // namespace sol1

namespace sol2 {

int partition(int arr[], int p, int r) {
    int i = p;
    int j = r;
    int q = (p + r) / 2;
    int x = arr[q];

    while (true) {
        while (arr[i] < x)
            ++i;

        while (x < arr[j])
            --j;

        if (i >= j)
            return i;

        std::swap(arr[i], arr[j]);
    }
}

void quickSort(int arr[], int p, int r) {
    if (p > r) return;
    int q = partition(arr, p, r);
    quickSort(arr, p, q - 1);
    quickSort(arr, q + 1, r);
}

void quickSort(int arr[], int n) {
    quickSort(arr, 0, n - 1);
}

} // namespace sol2


TEST_CASE("Quick sort", "[quick sort]") {
    int arr[] = {5, 2, 9, 1, 7, 7, 3, 6, 4, 8};
    int n = sizeof(arr)/sizeof(int);
    sol1::quickSort(arr, n);

    for (int i = 0; i < n; ++i) {
        printf("%d, ", arr[i]);
    }
    printf("\n");
}

} // namespace

