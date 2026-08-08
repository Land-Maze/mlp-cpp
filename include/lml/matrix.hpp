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

        static Matrix mul(const Matrix& A, const Matrix& B){
            assert(A.cols == B.rows);

            Matrix C(A.rows, B.cols);

            // FIXME: Optimize the naïve aproach
            for(size_t i = 0; i < C.rows; i++){
                for(size_t j = 0; j < C.cols; j++){
                    for(size_t m = 0; m < A.cols; m++){
                        C(i,j) += A(i, m) * B(m, j);
                    }
                }
            }

            return C;
        }
    };
}