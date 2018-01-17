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

} // namespace sol1

namespace sol2 {

// 중복원소 있을 때 제대로 동작 안 함!
int partition(int arr[], int p, int r) {
    int i = p;
    int j = r;
    int q = (p + r) / 2;
    int pivot = arr[q];

    while (i <= j) {
        if (arr[i] > pivot) { // 왼쪽 보고
            std::swap(arr[i], arr[j--]);
        } else if (arr[j] <= pivot) { // 오른쪽 보고
            std::swap(arr[i++], arr[j]);
        } else {
            i++;
            j--;
        }
    }
    return i - 1;
}

void quickSort(int arr[], int p, int r) {
    if (p > r) return;
    int q = partition(arr, p, r);
    quickSort(arr, p, q - 1);
    quickSort(arr, q + 1, r);
}

} // namespace sol2

namespace sol3 {

void partition(int arr[], int p, int r, int& l, int& u) {
    l = p;
    u = r;
    int pivot = arr[r];

    int i = l;
    while (i <= u) {
        if (arr[i] < pivot) {
            std::swap(arr[l++], arr[i++]);
        } else if (arr[i] > pivot) {
            std::swap(arr[i], arr[u--]);
        } else {
            i++;
        }
    }
}

void quickSort(int arr[], int p, int r) {
    if (p > r) return;
    int l, u;
    partition(arr, p, r, l, u);
    quickSort(arr, p, l - 1);
    quickSort(arr, u + 1, r);
}

} // namespace sol3


TEST_CASE("Quick sort", "[quick sort]") {
    int arr[] = {5, 2, 9, 1, 7, 7, 3, 6, 4, 8};
    int n = sizeof(arr)/sizeof(int);
    auto demo = [&](std::function<void(int[],int,int)> quickSort) {
        quickSort(arr, 0, n - 1);

        for (int i = 0; i < n; ++i) {
            printf("%d, ", arr[i]);
        }
        printf("\n");
    };

    demo(sol1::quickSort);
    //demo(sol2::quickSort);
    demo(sol3::quickSort);
}

} // namespace

