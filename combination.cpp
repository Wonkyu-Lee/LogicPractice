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

using Callback = function<void(int[], int)>;

void combRecurse(int arr[], int start, int end, int r, int result[], int index, Callback cb) {
    if (index == r) {
        cb(result, r);
        return;
    }

    for (int i = start; (i <= end) && (r - index <= end - i + 1); ++i) {
        result[index] = arr[i];
        combRecurse(arr, i + 1, end, r, result, index + 1, cb);

        if (arr[i] == arr[i + 1])
            ++i;
    }
}

void combination(int arr[], int n, int r, Callback cb) {
    int sorted[n];
    copy(arr, arr + n, sorted);
    sort(sorted, sorted + n);

    int result[r];
    combRecurse(sorted, 0, n - 1, r, result, 0, cb);
}

} // namespace solution1

namespace solution2 {

using Callback = function<void(int[], int)>;

void combRecurse(int arr[], int n, int r, int start, int result[], int index, Callback cb) {
    if (index == r) {
        cb(result, r);
        return;
    }

    if (n <= start) {
        return;
    }

    result[index] = arr[start];
    combRecurse(arr, n, r, start + 1, result, index + 1, cb);

    if (arr[start] == arr[start + 1])
        ++start;

    combRecurse(arr, n, r, start + 1, result, index, cb);
}

void combination(int arr[], int n, int r, Callback cb) {
    int sorted[n];
    copy(arr, arr + n, sorted);
    sort(sorted, sorted + n);

    int result[r];
    combRecurse(sorted, n, r, 0, result, 0, cb);
}

} // namespace solution2


namespace trace1 {

void combRecurse(int arr[], int start, int end, int r, int result[], int index, int indentation) {

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
            printf("%d, ", result[i]);
        }
        for (int i = index; i < r; ++i) {
            printf(", ");
        }
        printf("\b\b}, index:%d)\n", index);
    }

    if (index == r) {
        printIndent(indentation + 1);
        printf("return#1 result: {");
        for (int i = 0; i < r; ++i) {
            printf("%d, ", result[i]);
        }
        printf("\b\b}\n");
        return;
    }

    for (int i = start; (i <= end) && (r - index <= end - i + 1); ++i) {
        result[index] = arr[i];
        combRecurse(arr, i + 1, end, r, result, index + 1, indentation + 1);
        if (arr[i] == arr[i + 1]) {
            printIndent(indentation + 1);
            printf("skip arr[%d]\n", i + 1);
            ++i;
        }
    }

    printIndent(indentation + 1);
    printf("return#2\n");
}

void combination(int arr[], int n, int r) {
    int sorted[n];
    copy(arr, arr + n, sorted);
    sort(sorted, sorted + n);

    int result[r];
    combRecurse(sorted, 0, n - 1, r, result, 0, 0);
}

} // trace1

namespace trace2 {

void combRecurse(int arr[], int n, int r, int start, int result[], int index, int indentation) {

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
            printf("%d, ", result[i]);
        }
        for (int i = index; i < r; ++i) {
            printf(", ");
        }
        printf("\b\b})\n");
    }


    if (index == r) {
        {
            printIndent(indentation + 1);
            printf("return#1 result: {");
            for (int i = 0; i < r; ++i) {
                printf("%d, ", result[i]);
            }
            printf("\b\b}\n");
        }

        return;
    }

    if (n <= start) {
        {
            printIndent(indentation + 1);
            printf("return#2 [n: %d, start: %d]\n", n, start);
        }

        return;
    }

    result[index] = arr[start];
    combRecurse(arr, n, r, start + 1, result, index + 1, indentation + 1);

    if (arr[start] == arr[start + 1]) {
        printIndent(indentation + 1);
        printf("skip arr[%d]\n", start + 1);
        ++start;
    }

    combRecurse(arr, n, r, start + 1, result, index, indentation + 1);

    {
        printIndent(indentation + 1);
        printf("return#3\n");
    }
}

void combination(int arr[], int n, int r) {
    int sorted[n];
    copy(arr, arr + n, sorted);
    sort(sorted, sorted + n);

    int result[r];
    combRecurse(sorted, n, r, 0, result, 0, 0);
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
        int r = 3;

        printf("[Solution1] Combinations: \n");
        int count = 0;
        solution1::combination(array, n, r, [&count](int result[], int n) {
            for (int i = 0; i < n; ++i) {
                printf("%d ", result[i]);
            }
            printf("\n");
            ++count;
        });
        printf("\n");
    }

    SECTION("[Solution2] Visit possible combinations") {
        int array[] = {1, 2, 2, 3};
        int n = sizeof(array)/sizeof(int);
        int r = 3;

        printf("[Solution1] Combinations: \n");
        int count = 0;
        solution2::combination(array, n, r, [&count](int result[], int n) {
            for (int i = 0; i < n; ++i) {
                printf("%d ", result[i]);
            }
            printf("\n");
            ++count;
        });
        printf("\n");
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