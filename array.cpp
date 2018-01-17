//
// Created by blazeq on 2017. 11. 20..
//

#include "catch.hpp"

namespace {

template<typename T>
class Array2D {
    T** _array;
    int _rows;
    int _cols;

public:
    Array2D(int rows, int cols):_rows(rows), _cols(cols) {
        _array = new T*[rows];
        for (int i = 0; i < rows; ++i) {
            _array[i] = new T[cols];
        }
    }

    ~Array2D() {
        for (int i = 0; i < _rows; ++i) {
            delete [] _array[i];
        }
        delete [] _array;
    }

    T* operator[](int i) {
        return _array[i];
    }

    const T* operator[](int i) const {
        return _array[i];
    }

    int rows() const { return _rows; }
    int cols() const { return _cols; }
};

void printArray(const Array2D<int>& array) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 2; ++j) {
            printf("%3d", array[i][j]);
        }
        printf("\n");
    }
}

void test(int rows, int cols) {
    Array2D<int> array(rows, cols);

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            array[i][j] = i * rows + j;
        }
    }
    printArray(array);
}

TEST_CASE("Array", "[array]") {
    test(3, 2);
}

} // namespace