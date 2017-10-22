//
// Created by blazeq on 2017. 10. 22..
//

#include "catch.hpp"
#include <functional>
#include <cassert>
#include <unordered_set>

namespace {

using namespace std;

int countPermutations(int n, int r)
{
    assert (r <= n);

    if (r == 0)
        return 1;

    return n * countPermutations(n - 1, r - 1);
}

namespace solution1 {

using Callback = function<void(int[], int)>;

void permuComb(int arr[], int n, int r, int start, Callback cb) {
    if (start == r) {
        cb(arr, r);
        return;
    }

    unordered_set<int> swapped;

    for (int i = start; i < n; ++i) {
        // skip fixing duplicates
        if (swapped.find(arr[i]) != swapped.end())
            continue;

        swapped.insert(arr[i]);

        swap(arr[start], arr[i]);
        permuComb(arr, n, r, start + 1, cb);
        swap(arr[start], arr[i]);
    }
}

void permutation(int arr[], int n, int r, Callback cb) {
    permuComb(arr, n, r, 0, cb);
}

} // namespace solution1

TEST_CASE("Permutation", "[permutation]") {

    SECTION("Count possible permutations") {
        REQUIRE(countPermutations(3, 0) == 1);
        REQUIRE(countPermutations(3, 1) == 3);
        REQUIRE(countPermutations(3, 2) == 6);
        REQUIRE(countPermutations(3, 3) == 6);
    }

    SECTION("Visit possible permutations") {
        int arr[] = {0, 0, 1, 1};
        int count = 0;
        int n = sizeof(arr)/sizeof(int);
        int r = 3;
        solution1::permutation(arr, n, r, [&](int result[], int n) {
            for (int i = 0; i < n; ++i) {
                printf("%d ", result[i]);
            }
            printf("\n");
            ++count;
        });
        printf("\n");
    }
}

} // namespace