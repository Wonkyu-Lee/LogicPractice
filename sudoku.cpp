//
// Created by blazeq on 2018. 2. 18..
//
#include "catch.hpp"
#include <iostream>
#include <unordered_set>

using namespace std;

namespace {

class Sudoku {
    struct Cell {
        bool fixed{false};
        int value{0};
        unordered_set<int> candidates;
        Cell() {}
    };

    Cell table[9][9];

public:
    Sudoku(int sudoku[]) {
        for (int i = 0; i < 81; ++i) {
            int r = i / 9;
            int c = i % 9;
            table[r][c].value = sudoku[i];
        }

        updateCandidates();
        goForward();
    }

    void updateCandidates() {
        for (int r = 0; r < 9; ++r) {
            for (int c = 0; c < 9; ++c) {
                if (table[r][c].value == 0) {
                    updateCandidates(r, c);
                } else {
                    table[r][c].fixed = true;
                }
            }
        }
    }

    void updateCandidates(int r, int c) {
        bool possible[10];
        for (int i = 0; i <= 9; ++i) {
            possible[i] = true;
        }

        for (int i = 0; i < 9; ++i) {
            int value = table[i][c].value;
            possible[value] = false;
        }

        for (int i = 0; i < 9; ++i) {
            int value = table[r][i].value;
            possible[value] = false;
        }

        int chunkRow = r / 3;
        int chunkCol = c / 3;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                int row = chunkRow * 3 + i;
                int col = chunkCol * 3 + j;
                int value = table[row][col].value;
                possible[value] = false;
            }
        }

        for (int i = 1; i <= 9; ++i) {
            if (possible[i]) {
                table[r][c].candidates.insert(i);
            }
        }
    }

    void goForward() {
        bool updated = true;

        while (updated) {
            updated = false;

            for (int r = 0; r < 9; ++r) {
                for (int c = 0; c < 9; ++c) {
                    if (!table[r][c].fixed) {
                        int debug = table[r][c].candidates.size();
                        if (table[r][c].candidates.size() == 1) {
                            int value = *table[r][c].candidates.begin();
                            table[r][c].candidates.clear();
                            table[r][c].value = value;
                            table[r][c].fixed = true;
                            updated = true;
                        }
                    }

                }
            }
        }
    }

    void print() {
        for (int r = 0; r < 9; ++r) {
            for (int c = 0; c < 9; ++c) {
                cout << table[r][c].value << " ";
            }
            cout << endl;
        }
    }
};

}

TEST_CASE("Sudoku", "[sudoku]") {

//    SECTION("Sudoku 1") {
//        int input[] ={
//            3, 0, 6, 5, 0, 8, 4, 0, 0,
//            5, 2, 0, 0, 0, 0, 0, 0, 0,
//            0, 8, 7, 0, 0, 0, 0, 3, 1,
//            0, 0, 3, 0, 1, 0, 0, 8, 0,
//            9, 0, 0, 8, 6, 3, 0, 0, 5,
//            0, 5, 0, 0, 9, 0, 6, 0, 0,
//            1, 3, 0, 0, 0, 0, 2, 5, 0,
//            0, 0, 0, 0, 0, 0, 0, 7, 4,
//            0, 0, 5, 2, 0, 6, 3, 0, 0
//        };
//
//        Sudoku sudoku(input);
//        sudoku.print();
//    }

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
        sudoku.print();
    }
}