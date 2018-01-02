//
// Created by blazeq on 2017. 12. 22..
//

#include <iostream>
#include <vector>
#include "catch.hpp"

namespace {

using namespace std;

namespace recursive {
/*
 * minJumps(array, start) = 1 + min{minJumps(array, start + k)} // 1 <= k <= array[start]
 * if array[start] == 0, return error
 */
int countMinJumps(const vector<int>& array, int start) {
    static const int INFINITE = numeric_limits<int>::max();

    int m = array.size();
    if (m == 0) return INFINITE;

    if (start == m - 1) {
        return 0;
    }

    if (array[start]== 0) return INFINITE;

    int minJumps = INFINITE;
    for (int i = start + 1; (i <= start + array[start] && i < m); ++i) {
        int jumps = countMinJumps(array, i);
        minJumps = min(minJumps, jumps);
    }

    minJumps = (minJumps == INFINITE) ? INFINITE : minJumps + 1;

    return minJumps;
}

int countMinJumps(const vector<int>& array) {
    return countMinJumps(array, 0);
}

} // recursive

namespace dp {

int countMinJumps(const vector<int>& array)
{
    static const int INFINITE = numeric_limits<int>::max();
    int n = array.size();
    if (n == 0) return INFINITE;

    int jumps[n];
    jumps[n - 1] = 0;
    for (int i = n - 2; 0 <= i; --i) {
        if (array[i] == 0) {
            jumps[i] = INFINITE;
        } else if (n - 1 <= i + array[i]) {
            jumps[i] = 1;
        } else {
            int minJumps = INFINITE;
            for (int j = i + 1; j <= i + array[i] && j < n; ++j) {
                minJumps = min(minJumps, jumps[j]);
            }
            jumps[i] = (minJumps == INFINITE) ? INFINITE : minJumps + 1;
        }
    }
    return jumps[0];
}

} // dp

TEST_CASE("min jumps", "[min jumps]") {
    vector<int> array{1, 3, 5, 8, 9, 2, 6, 7, 6, 8, 9};
    REQUIRE(recursive::countMinJumps(array) == 3);
    REQUIRE(dp::countMinJumps(array) == 3);
}

} // namespace