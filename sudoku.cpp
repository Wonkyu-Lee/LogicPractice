//
// Created by blazeq on 2018. 2. 18..
//
#include "catch.hpp"
#include <iostream>
#include <unordered_set>

using namespace std;

namespace {

class Sudoku {
    enum { M = 3, N = 9 };
    int table[N][N];

public:
    Sudoku(int sudoku[]) {
        for (int i = 0; i < N * N; ++i) {
            int r = i / N;
            int c = i % N;
            table[r][c] = sudoku[i];
        }
    }


    void print() {
        for (int r = 0; r < N; ++r) {
            for (int c = 0; c < N; ++c) {
                cout << table[r][c] << " ";
            }
            cout << endl;
        }
    }

    bool solve() {
        int row, col;
        if (!findEmptySlot(row, col)) {
            return true;
        }

        for (int num = 1; num <= N; ++num) {
            if (!used(row, col, num)) {
                table[row][col] = num;
                if (solve()) {
                    return true;
                }
                table[row][col] = 0;
            }
        }

        return false;
    }

private:
    bool findEmptySlot(int& row, int& col) {
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                if (table[i][j] == 0) {
                    row = i;
                    col = j;
                    return true;
                }
            }
        }

        return false;
    }

    bool used(int row, int col, int num) {
        return usedInRow(row, num) ||
               usedInCol(col, num) ||
               usedInBlock(row, col, num);
    }

    bool usedInRow(int row, int num) {
        for (int i = 0; i < N; ++i) {
            if (table[row][i] == num) {
                return true;
            }
        }

        return false;
    }

    bool usedInCol(int col, int num) {
        for (int i = 0; i < N; ++i) {
            if (table[i][col] == num) {
                return true;
            }
        }

        return false;
    }

    bool usedInBlock(int row, int col, int num) {
        int rGroup = row / M;
        int cGroup = col / M;

        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < M; ++j) {
                int r = rGroup * M + i;
                int c = cGroup * M + j;
                if (table[r][c] == num) {
                    return true;
                }
            }
        }

        return false;
    }
};

}

TEST_CASE("Sudoku", "[sudoku]") {

    SECTION("Sudoku 1") {
        int input[] ={
            3, 0, 6, 5, 0, 8, 4, 0, 0,
            5, 2, 0, 0, 0, 0, 0, 0, 0,
            0, 8, 7, 0, 0, 0, 0, 3, 1,
            0, 0, 3, 0, 1, 0, 0, 8, 0,
            9, 0, 0, 8, 6, 3, 0, 0, 5,
            0, 5, 0, 0, 9, 0, 6, 0, 0,
            1, 3, 0, 0, 0, 0, 2, 5, 0,
            0, 0, 0, 0, 0, 0, 0, 7, 4,
            0, 0, 5, 2, 0, 6, 3, 0, 0
        };

        Sudoku sudoku(input);
        bool success = sudoku.solve();
        cout << (success ? "Success" : "Failed") << endl;
        sudoku.print();
    }

    SECTION("Sudoku 2") {
        int input[] = {
            3, 6, 7, 5, 3, 5, 6, 2, 9,
            1, 2, 7, 0, 9, 3, 6, 0, 6,
            2, 6, 1, 8, 7, 9, 2, 0, 2,
            3, 7, 5, 9, 2, 2, 8, 9, 7,
            3, 6, 1, 2, 9, 3, 1, 9, 4,
            7, 8, 4, 5, 0, 3, 6, 1, 0,
            6, 3, 2, 0, 6, 1, 5, 5, 4,
            7, 6, 5, 6, 9, 3, 7, 4, 5,
            2, 5, 4, 7, 4, 4, 3, 0, 7
        };

        Sudoku sudoku(input);
        bool success = sudoku.solve();
        cout << (success ? "Success" : "Failed") << endl;
        sudoku.print();
    }
}