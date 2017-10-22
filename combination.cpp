//
// Created by blazeq on 2017. 10. 21..
//

#include "catch.hpp"
#include <functional>

namespace {

using namespace std;

int countCombinations(int n, int r) {
    if (n == r || r == 0) {
        return 1;
    }

    return countCombinations(n - 1, r - 1) + countCombinations(n - 1, r);
}

namespace solution1 {

using Visitor = function<void(int*, int)>;

void visitCombinationsRecurse(int* array, int* combination, int start, int end, int index, int r, Visitor visit) {
    if (index == r) {
        visit(combination, r);
        return;
    }

    for (int i = start; (i <= end) && (r - index <= end - i + 1); ++i) {
        combination[index] = array[i];
        visitCombinationsRecurse(array, combination, i + 1, end, index + 1, r, visit);

        if (array[i] == array[i + 1])
            ++i;
    }
}

void visitCombinations(int* array, int n, int r, Visitor visit) {
    int copy[n];
    for (int i = 0; i < n; ++i) { copy[i] = array[i]; }
    sort(copy, copy + n);

    int combination[r];
    visitCombinationsRecurse(copy, combination, 0, n - 1, 0, r, visit);
}

} // namespace solution1

namespace solution2 {

using Visitor = function<void(int*, int)>;

void visitCombinationsRecurse(int* array, int n, int r, int index, int* combination, int start, Visitor visit) {
    if (index == r) {
        visit(combination, r);
        return;
    }

    if (n <= start) {
        return;
    }

    combination[index] = array[start];
    visitCombinationsRecurse(array, n, r, index + 1, combination, start + 1, visit);

    if (array[start] == array[start + 1])
        ++start;

    visitCombinationsRecurse(array, n, r, index, combination, start + 1, visit);
}

void visitCombinations(int* array, int n, int r, Visitor visit) {
    int copy[n];
    for (int i = 0; i < n; ++i) { copy[i] = array[i]; }
    sort(copy, copy + n);

    int combination[r];
    visitCombinationsRecurse(copy, n, r, 0, combination, 0, visit);
}

} // namespace solution2


namespace trace1 {

void combRecurse(int arr[], int start, int end, int r, int data[], int index, int indentation) {

    auto printIndent = [](int indentation) {
        for (int i = 0; i < indentation; ++i) {
            printf("    ");
        }
    };

    {
        printIndent(indentation);
        printf("combRecurs(arr:{");
        for (int i = start; i <= end; ++i) {
            printf("%d, ", arr[i]);
        }
        if (start <= end)
            printf("\b\b");
        printf("}, start:%d, end:%d, r:%d, data:{", start, end, r);
        for (int i = 0; i < index; ++i) {
            printf("%d, ", data[i]);
        }
        for (int i = index; i < r; ++i) {
            printf(", ");
        }
        printf("\b\b}, index:%d)\n", index);
    }

    if (index == r) {
        printIndent(indentation + 1);
        printf("return1 combination: {");
        for (int i = 0; i < r; ++i) {
            printf("%d, ", data[i]);
        }
        printf("\b\b}\n");
        return;
    }

    for (int i = start; (i <= end) && (r - index <= end - i + 1); ++i) {
        data[index] = arr[i];
        combRecurse(arr, i + 1, end, r, data, index + 1, indentation + 1);
        if (arr[i] == arr[i + 1]) {
            printIndent(indentation + 1);
            printf("skip arr[%d]\n", i + 1);
            ++i;
        }
    }

    printIndent(indentation + 1);
    printf("return2\n");
}

void combination(int arr[], int n, int r) {
    int data[r];
    sort(arr, arr + n);
    combRecurse(arr, 0, n - 1, r, data, 0, 0);
}

} // trace1

namespace trace2 {

// Call tracking
void combRecurse(int arr[], int n, int r, int start, int data[], int index, int indentation) {

    auto printIndent = [](int indentation) {
        for (int i = 0; i < indentation; ++i) {
            printf("    ");
        }
    };

    {
        printIndent(indentation);
        printf("combRecurse(arr:{");
        for (int i = start; i < n; ++i) {
            printf("%d, ", arr[i]);
        }
        if (start < n)
            printf("\b\b");
        printf("}, index: %d, data:{", index);
        for (int i = 0; i < index; ++i) {
            printf("%d, ", data[i]);
        }
        for (int i = index; i < r; ++i) {
            printf(", ");
        }
        printf("\b\b})\n");
    }


    if (index == r) {
        {
            printIndent(indentation + 1);
            printf("return1 combination: {");
            for (int i = 0; i < r; ++i) {
                printf("%d, ", data[i]);
            }
            printf("\b\b}\n");
        }

        return;
    }

    if (n <= start) {
        {
            printIndent(indentation + 1);
            printf("return2 [n: %d, start: %d]\n", n, start);
        }

        return;
    }

    data[index] = arr[start];
    combRecurse(arr, n, r, start + 1, data, index + 1, indentation + 1);

    if (arr[start] == arr[start + 1]) {
        printIndent(indentation + 1);
        printf("skip arr[%d]\n", start + 1);
        ++start;
    }

    combRecurse(arr, n, r, start + 1, data, index, indentation + 1);

    {
        printIndent(indentation + 1);
        printf("return3\n");
    }
}

void combination(int arr[], int n, int r) {
    int data[r];
    sort(arr, arr + n);
    combRecurse(arr, n, r, 0, data, 0, 0);
}

} // namespace trace2




TEST_CASE("Combination", "[combination]") {

    SECTION("Count possible combinations") {
        REQUIRE(countCombinations(5, 2) == 10);
        REQUIRE(countCombinations(5, 2) == countCombinations(5, 3));
    }

    SECTION("[Solution1] Visit possible combinations") {
        int array[] = {1, 2, 2, 3};
        int n = sizeof(array)/sizeof(int);
        int r = 2;

        printf("[Solution1] Combinations: \n");
        int count = 0;
        solution1::visitCombinations(array, n, r, [&count](int* array, int n) {
            for (int i = 0; i < n; ++i) {
                printf("%d ", array[i]);
            }
            printf("\n");
            ++count;
        });
    }

    SECTION("[Solution2] Visit possible combinations") {
        int array[] = {1, 2, 2, 3};
        int n = sizeof(array)/sizeof(int);
        int r = 2;

        printf("[Solution1] Combinations: \n");
        int count = 0;
        solution2::visitCombinations(array, n, r, [&count](int* array, int n) {
            for (int i = 0; i < n; ++i) {
                printf("%d ", array[i]);
            }
            printf("\n");
            ++count;
        });
    }

    SECTION("[Trace1]") {
        printf("[Trace1]\n");
        int array[] = {2, 1, 0, 1};
        trace1::combination(array, 4, 3);
        printf("\n");
    }

    SECTION("[Trace2]") {
        printf("[Trace2]\n");
        int array[] = {2, 1, 0, 1};
        trace2::combination(array, 4, 3);
        printf("\n");
    }
}

} // namespace