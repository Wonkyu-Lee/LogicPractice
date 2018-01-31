//
// Created by blazeq on 2018. 1. 27..
//

#include <list>
#include <iostream>
#include "catch.hpp"

namespace {

using namespace std;

list<int> getPrimes(int n) {
    list<int> primes;

    if (n < 2) return primes;

    bool prime[n + 1];
    for (int i = 2; i <= n; ++i)
        prime[i] = true;

    for (int i = 2; i * i <= n; ++i) {
        if (prime[i]) {
            for (int j = i * i; j <= n; j += i) {
                prime[j] = false;
            }
        }
    }

    for (int i = 2; i <= n; ++i) {
        if (prime[i])
            primes.push_back(i);
    }

    return primes;
}

} // namespace

TEST_CASE("Sieve of Eratosthenes", "[eratosthenes]") {
    list<int> primes = getPrimes(100);
    for (auto each : primes) {
        cout << each << " ";
    }
    cout << endl;
}