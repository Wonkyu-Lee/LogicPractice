//
// Created by blazeq on 2017. 12. 27..
//

#include "catch.hpp"
#include <iostream>

namespace {

using namespace std;

int catalanDp(int n) {
    int ctl[n + 1];
    ctl[0] = 1;

    for (int i = 1; i <= n; ++i) {
        ctl[i] = 0;
        for (int j = 0; j < i; ++j) {
            ctl[i] += ctl[j] * ctl[i - 1 - j];
        }
    }

    return ctl[n];
}

int binomialCoefficient(int n, int k) {
    if (n - k < k)
        k = n - k;

    int r = 1;
    for (int i = 0; i < k; ++i) {
        r *= n - i;
        r /= i + 1;
    }
    return r;
}

int catalan(int n) {
    return binomialCoefficient(2 * n, n) / (n + 1);
}

TEST_CASE("catalan", "[catalan]") {

    int n = 10;
    for (int i = 0; i <= n; ++i) {
        printf("catalanDP(%d) = %d, catalan(%d) = %d\n", i, catalanDp(i), i, catalan(i));
    }

}

} // namespace