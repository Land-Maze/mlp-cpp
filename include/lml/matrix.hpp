#pragma once

#include <vector>
#include <cassert>

namespace LML{
    struct Matrix{
        std::vector<float> data;
        size_t rows;
        size_t cols;

        Matrix(int rows, int cols) : data(rows * cols, 0.0f), rows(rows), cols(cols) {}

        inline float& operator()(size_t row, size_t col) {
            return data[row * cols + col];
        }

        inline float operator()(size_t row, size_t col) const {
            return data[row * cols + col];
        }

        static Matrix mul(const Matrix& A, const Matrix& B);

        static Matrix mul_transposed_A(const Matrix& A, const Matrix& B);
    };

    inline void assert_dim_equal(const Matrix& A, const Matrix& B){
        assert(A.rows == B.rows && A.cols == B.cols);
    };
}