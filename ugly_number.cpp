//
// Created by blazeq on 2017. 12. 21..
//

#include "catch.hpp"

namespace {

using namespace std;

int uglyNumber(int n) {
    int s[n];
    s[0] = 1;
    int size = 1;

    int prime[3] = {2, 3, 5};
    int index[3] = {0, 0, 0};

    while (size < n) {
        int minValue = numeric_limits<int>::max();

        for (int i = 0; i < 3; ++i) {
            int v = prime[i] * s[index[i]];
            if (v < minValue) minValue = v;
        }

        s[size++] = minValue;

        for (int i = 0; i < 3; ++i) {
            int v = prime[i] * s[index[i]];
            if (v == minValue)
                index[i]++;
        }
    }

    return s[size - 1];
}

TEST_CASE("ugly number", "[ugly number]") {
    REQUIRE(uglyNumber(1) == 1);
    REQUIRE(uglyNumber(2) == 2);
    REQUIRE(uglyNumber(150) == 5832);
}

} // namespace