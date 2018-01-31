//
// Created by blazeq on 2018. 1. 23..
//

#include "catch.hpp"
#include <iostream>

namespace {

using namespace std;

bool solve(int* array, int n, int targetSum) {
    if (n == 0) {
        return false;
    }

    for (int size = 1; size <= n; ++size) {
        for (int i = 0; i < n - size; ++i) {
            int sum = 0;
            int l = i;
            int r = i + size - 1;
            for (int j = l; j <= r; ++j) {
                sum += array[j];
            }
            if (sum == targetSum) {

                // print
                for (int k = l; k <= r; ++k) {
                    cout << array[k] << " ";
                }
                cout << endl;

                return true;
            }
        }
    }

    return false;
}

// https://ide.geeksforgeeks.org/nW0uaUgW0U
bool solve2(int* array, int n, int targetSum) {
    if (n == 0) {
        return false;
    }

    int l = 0;
    int r = 0;
    int sum = array[0];
    while (l <= r) {
        bool lMove = false;
        bool rMove = false;
        if (sum == targetSum) {

            // print
            for (int i = l; i <= r; ++i) {
                cout << array[i] << " ";
            }
            cout << endl;

            return true;
        } else if (sum < targetSum) {
            if (r == n - 1) {
                return false;
            }
            rMove = true;
        } else {
            if (l == n - 1) {
                return false;
            }
            lMove = true;
            if (l == r) {
                rMove = true;
            }
        }

        if (lMove) {
            sum -= array[l];
            ++l;
        }

        if (rMove) {
            ++r;
            sum += array[r];
        }
    }

    return false;
}

} // namespace

TEST_CASE("Subarrays with target sum", "[subarrays with target sum]") {
    int array[] = {1, 4, 7, 3, 2};
    int n = sizeof(array) / sizeof(int);
    int targetSum = 14;

    bool exists = solve(array, n, targetSum);
    cout << "exists target sum? " << (exists ? "yes" : "no") << endl;
}