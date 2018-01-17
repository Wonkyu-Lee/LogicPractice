//
// Created by blazeq on 2018. 1. 13..
//

#include "catch.hpp"
#include <iostream>

namespace {

using namespace std;

string divide(const string& number, int divisor) {
    if (divisor == 0) {
        return "NaN";
    }

    stringstream ss;
    int current = 0;
    bool started = false; // 이렇게 했다.

    for (int i = 0; i < number.length(); ++i) {
        current = 10 * current + stoi(number.substr(i, 1));
        if (current < divisor) {
            if (started)
                ss << '0';
            continue;
        }

        ss << current/divisor;
        current = current % divisor;
        started = true;
    }

    return ss.str();
}

} // namespace

TEST_CASE("Divide string large number", "[divide string large number]") {
    REQUIRE(divide("12313413534672234", 754) == "16330787181262");
}