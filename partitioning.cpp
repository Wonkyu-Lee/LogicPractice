//
// Created by blazeq on 2018. 1. 8..
//

#include "catch.hpp"
#include <iostream>

namespace {

using namespace std;

struct Partition {
    int leftSize;
    int middleSize;
    Partition(int leftSize, int middleSize): leftSize(leftSize), middleSize(middleSize){}
};

Partition threeWayPartition(int array[], int n, int lower, int upper) {
    int s = 0;
    int e = n - 1;

    int i = 0;
    while (i <= e) {
        if (array[i] < lower) {
            swap(array[i++], array[s++]);
        } else if (array[i] > upper) {
            swap(array[i], array[e--]);
        } else {
            i++;
        }
    }

    return Partition(s, e - s + 1);
}

TEST_CASE("Three way partition", "[3-way partition]") {
    int array[] = {1, 14, 5, 20, 4, 2, 54, 20, 87, 98, 3, 1, 32};
    int n = sizeof(array)/sizeof(int);

    Partition r = threeWayPartition(array, n, 20, 20);

    for (int i = 0; i < n; ++i) {
        cout << array[i] << " ";
    }
    cout << endl;

    cout << "left: ";
    for (int i = 0; i < r.leftSize; ++i) {
        cout << array[i] << " ";
    }
    cout << endl;

    cout << "middle: ";
    for (int i = r.leftSize; i < r.leftSize + r.middleSize; ++i) {
        cout << array[i] << " ";
    }
    cout << endl;

    cout << "right: ";
    for (int i = r.leftSize + r.middleSize; i < n; ++i) {
        cout << array[i] << " ";
    }
    cout << endl;
}

} // namespace