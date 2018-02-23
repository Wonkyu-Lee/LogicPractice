//
// Created by blazeq on 2018. 1. 7..
//

#include "catch.hpp"
#include <iostream>

namespace {

using namespace std;

void findPairs(int array[], int n, int target, function<void(vector<int>&)> callback) {
    sort(array, array + n);

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
    sort(array, array + n);

    for (int i = 0; i < n - 2; ++i) {
        auto cbPair = [&](vector<int>& v) {
            vector<int> triplet(3);
            triplet[0] = array[0];
            triplet[1] = v[0];
            triplet[2] = v[1];
            callback(triplet);
        };

        findPairs(array + i + 1, n - 1 - i, sum - array[i], cbPair);
    }
}

void findSubsetSizeK(int array[], int s, int e, int k, int sum, vector<int>& result, function<void(vector<int>&)> callback) {
    if (k == 0) {
        return;
    }

    if (k == 1) {
        if (binary_search(array + s, array + e + 1, sum)) {
            result.push_back(sum);
            callback(result);
        }
        return;
    }

    if (k == 2) {
        int l = s;
        int r = e;

        while(l < r) {
            int value = array[l] + array[r];
            if (value == sum) {
                result.push_back(array[l]);
                result.push_back(array[r]);
                callback(result);
                result.pop_back();
                result.pop_back();
                ++l;
                --r;
            } else if (value < sum) {
                ++l;
            } else {
                --r;
            }
        }

        return;
    }

    for (int i = s; i <= e - k + 1; ++i) {
        result.push_back(array[i]);
        findSubsetSizeK(array, i + 1, e, k - 1, sum - array[i], result, callback);
        result.pop_back();
    }
}

void findSubsetSizeK(int array[], int n, int k, int sum, function<void(vector<int>&)> callback) {
    sort(array, array + n);
    vector<int> result;
    findSubsetSizeK(array, 0, n - 1, k, sum, result, callback);
}

} // namespace

TEST_CASE("Subsets with target sum", "[subsets_with_target_sum]") {
    int array[] = {1, 2, 4, 4, 45, 6, 10, -8, 12};
    int n = sizeof(array)/sizeof(int);

    auto print = [](vector<int>& v) {
        stringstream o;
        for (int i = 0; i < v.size(); ++i) {
            if (i == 0) {
                o << "(";
            }

            o << v[i];

            if (i < v.size() - 1) {
                o << ", ";
            } else {
                o << ")";
            }
        }
        cout << o.str();
    };

//    findPairs(array, n, 16, print);
//    findTriplets(array, n, 2, print);

//    cout << "k=0, target sum = 16" << endl;
//    findSubsetSizeK(array, n, 0, 16, print);
//    cout << endl;
//
//    cout << "k=1, target sum = 45" << endl;
//    findSubsetSizeK(array, n, 1, 45, print);
//    cout << endl;
//
//    cout << "k=2, target sum = 16" << endl;
//    findSubsetSizeK(array, n, 2, 16, print);
//    cout << endl;
//
//    cout << "k=3, target sum = 11" << endl;
//    findSubsetSizeK(array, n, 3, 11, print);
//    cout << endl;
//
//    cout << "k=4, target sum = 20" << endl;
//    findSubsetSizeK(array, n, 4, 20, print);
//    cout << endl;

    cout << "k=2, target sum = 8" << endl;
    findSubsetSizeK(array, n, 2, 6, print);
    cout << endl;
}