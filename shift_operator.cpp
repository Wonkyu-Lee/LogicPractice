//
// Created by blazeq on 2018. 2. 5..
//

#include "catch.hpp"
#include <bitset>
#include <iostream>

using namespace std;

namespace {



} // namespace

TEST_CASE("Logical shift", "[logical shift]") {
    short x = 2;

    x = x << 1;

    bitset<16> r(x);
    cout << r << endl;
}