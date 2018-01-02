//
// Created by blazeq on 2017. 11. 20..
//

#include "catch.hpp"

namespace {

void printArray(int** arr) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 2; ++j) {
            printf("%3d", arr[i][j]);
        }
        printf("\n");
    }
}

TEST_CASE("Array", "[array]") {
    int arr[][2] = { {1, 2}, {3, 4}, {5, 6} };
    printArray((int**)arr);
}

} // namespace