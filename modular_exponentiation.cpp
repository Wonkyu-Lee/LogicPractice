//
// Created by blazeq on 2017. 11. 14..
//

#include "catch.hpp"

namespace {

int power(int x, int y) {
    int result = 1;
    while (y != 0) {
        if (y & 1) {
            result *= x;
        }

        y = y >> 1;
        x = x * x;
    }

    return result;
}

int powerModular(int x, int y, int p) {
    int result = 1;
    x = x % p;
    while (y != 0) {
        if (y & 1) {
            result  = (result * x) % p;
        }

        y = y >> 1;
        x = (x * x) % p;
    }

    return result;
}

TEST_CASE("Modular exponentiation", "[modular exponentiation]") {

    REQUIRE(power(2, 10) == 1024);
    REQUIRE(power(3, 5) == 243);

    REQUIRE(powerModular(2, 10, 7) == 1024 % 7);
    REQUIRE(powerModular(3, 5, 7) == 243 % 7);
}

} // namespace