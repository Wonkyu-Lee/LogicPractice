//
// Created by blazeq on 2017. 10. 26..
//

#include "catch.hpp"
#include <iostream>

using namespace std;

namespace sol1 {

int fibonacci(int n) {
    if (n == 0 || n == 1)
        return n;

    return fibonacci(n - 1) + fibonacci(n - 2);
}

} // namespace sol1

namespace sol2 {

int fibonacci(int n, int m[]) {
    if (m[n] == -1) {
        m[n] = fibonacci(n - 1, m) + fibonacci(n - 2, m);
    }

    return m[n];
}

int fibonacci(int n) {
    int m[n + 1];
    for (int i = 2; i <= n; ++i)
        m[i] = -1;

    m[0] = 0;
    m[1] = 1;
    return fibonacci(n, m);
}

} // namespace sol2

namespace sol3 {

int fibonacci(int n) {
    int m[n + 1];
    m[0] = 0;
    m[1] = 1;
    for (int i = 2; i <= n; ++i) {
        m[i] = m[i - 1] + m[i - 2];
    }

    return m[n];
}

} // namespace sol3

namespace sol4 {

int fibonacci(int n) {
    if (n == 0 || n == 1)
        return n;

    int a = 0;
    int b = 1;
    for (int i = 2; i < n; ++i) {
        int c = a + b;
        a = b;
        b = c;
    }

    return a + b;
}

} // namespace sol4

TEST_CASE("Fibonacci", "[fibonacci]") {
    REQUIRE(sol1::fibonacci(10) == 55);
    REQUIRE(sol2::fibonacci(10) == 55);
    REQUIRE(sol3::fibonacci(10) == 55);
    REQUIRE(sol4::fibonacci(10) == 55);
}