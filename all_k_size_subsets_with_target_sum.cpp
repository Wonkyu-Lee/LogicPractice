//
// Created by blazeq on 2018. 1. 7..
//

#include "catch.hpp"
#include <iostream>

namespace {

using namespace std;

void findPairs(int array[], int n, int target, function<void(vector<int>&)> callback) {
    int l = 0;
    int r = n - 1;
    while (l < r) {
        int sum = array[l] + array[r];
        if (sum == target) {
            vector<int> pair(2);
            pair[0] = array[l];
            pair[1] = array[r];
            callback(pair);
            ++l;
            --r;
        } else if (sum < target) {
            ++l;
        } else {
            --r;
        }
    }
}

void findTriplets(int array[], int n, int sum, function<void(vector<int>&)> callback) {
    for (int i = 0; i < n - 2; ++i) {
        auto cbPair = [&](vector<int>& v) {
            vector<int> triplet(3);
            triplet[0] = array[0];
            triplet[1] = v[0];
            triplet[2] = v[1];
            callback(triplet);
        };
        findPairs(array + 1, n - 1, sum - array[i], cbPair);
    }
}

} // namespace

TEST_CASE("Subsets with target sum", "[subsets_with_target_sum]") {
    int array[] = {1, 4, 45, 6, 10, -8, 12};
    int n = sizeof(array)/sizeof(int);

    auto print = [](vector<int>& v) {
        for (auto e : v) {
            cout << e << " ";
        }
        cout << endl;
    };

    sort(array, array + n);
    findPairs(array, n, 16, print);
    findTriplets(array, n, 2, print);
}