//
// Created by blazeq on 2018. 2. 11..
//

#include "catch.hpp"
using namespace std;

namespace {

int find(int arr[], int s, int e, int x, bool lowerBound) {
    if (s > e) {
        return lowerBound ? e : s;
    }

    int m = (s + e) / 2;
    if (x < arr[m]) {
        return find(arr, s, m - 1, x, lowerBound);
    } else if (arr[m] < x) {
        return find(arr, m + 1, e, x, lowerBound);
    } else {
        int x = arr[m];

        if (lowerBound) {
            while (s <= m - 1 && arr[m - 1] == x) {
                --m;
            }
            return m;
        } else {
            while (m + 1 <= e && arr[m + 1] == x) {
                ++m;
            }
            return m;
        }
    }
}

pair<int, int> getInclusion(int arr[], int s, int e, const pair<int, int>& range) {
    int start = max(s, find(arr, s, e, range.first, true));
    int end = min(e, find(arr, s, e, range.second, false));
    return make_pair(start, end);
};

void test() {
    int arr[] = {2, 4, 5, 5, 5, 6, 8, 10, 12, 14, 15, 15, 15, 16};
    int n = sizeof(arr) / sizeof(int);
    auto range = make_pair(5, 15);

    pair<int, int> inclusion = getInclusion(arr, 0, n - 1, range);
    printf("[%d, %d]\n", inclusion.first, inclusion.second);
}

} // namespace

TEST_CASE("Inclusion", "[inclusion]") {
    test();
}