//
// Created by blazeq on 2018. 1. 30..
//

#include "catch.hpp"
#include <string>
#include <stack>
#include <iostream>

namespace {

using namespace std;

/* Input
 * {76, 78, 80, 71, 73, 75, 82, 68, 65}
 *
 * Output
 * {1, 1, 4, 1, 1, 1, -1, -1, -1}
 */
void printDistanceToGreater(int array[], int n) {
    int distance[n];
    stack<int> s;

    for (int i = 0; i < n; ++i) {
        while (!s.empty() && array[s.top()] < array[i]) {
            distance[s.top()] = i - s.top();
            s.pop();
        }
        s.push(i);
    }

    while (!s.empty()) {
        distance[s.top()] = -1;
        s.pop();
    }

    for (int i = 0; i < n; ++i) {
        cout << distance[i] << " ";
    }
    cout << endl;
}

} // namespace

TEST_CASE("Distance to greater", "[distance to greater]") {
    int array[] = {76, 78, 80, 71, 73, 75, 82, 68, 65};
    int n = sizeof(array) / sizeof(int);

    printDistanceToGreater(array, n);
}