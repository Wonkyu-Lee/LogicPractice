//
// Created by blazeq on 2017. 11. 9..
//

#include "catch.hpp"

namespace sol1 {

void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; ++i) {
        int j = i - 1;
        while(0 <= j && arr[j + 1] < arr[j]) {
            std::swap(arr[j], arr[j + 1]);
            --j;
        }
    }
}

} // namespace sol1

TEST_CASE("Insertion sort", "[insertion sort]") {
    int arr[] = {5, 2, 9, 1, 7, 7, 3, 6, 4, 8};
    int n = sizeof(arr)/sizeof(int);
    sol1::insertionSort(arr, n);

    for (int i = 0; i < n; ++i) {
        printf("%d, ", arr[i]);
    }
    printf("\n");
}

