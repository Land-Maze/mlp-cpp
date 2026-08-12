#include <lml/matrix.hpp>
#include <cassert>

using namespace LML;

Matrix Matrix::mul(const Matrix &A, const Matrix &B)
{
    assert(A.cols == B.rows);

    Matrix C(A.rows, B.cols);

    // FIXME: Optimize the naïve aproach
    for (size_t i = 0; i < C.rows; i++)
    {
        for (size_t j = 0; j < C.cols; j++)
        {
            for (size_t m = 0; m < A.cols; m++)
            {
                C(i, j) += A(i, m) * B(m, j);
            }
        }
    }

    return C;
}

Matrix Matrix::mul_transposed_A(const Matrix &A, const Matrix &B)
{
    assert(A.cols == B.rows);

    Matrix C(A.rows, B.cols);

    // FIXME: Optimize the naïve aproach
    for (size_t i = 0; i < C.rows; i++)
    {
        for (size_t j = 0; j < C.cols; j++)
        {
            for (size_t m = 0; m < A.cols; m++)
            {
                C(i, j) += A(m, i) * B(m, j);
            }
        }
    }

Matrix Matrix::mul_transposed_B(const Matrix &A, const Matrix &B){
    assert(A.cols == B.cols);

    Matrix C(A.rows, B.rows);

    // FIXME: Optimize the naïve aproach
    for (size_t i = 0; i < C.rows; i++)
    {
        for (size_t j = 0; j < C.cols; j++)
        {
            for (size_t m = 0; m < A.cols; m++)
            {
                C(i, j) += A(i, m) * B(j, m);
            }
        }
    }

    return C;
}

Matrix Matrix::add(const Matrix &A, const Matrix &B){
    assert_dim_equal(A, B);

    Matrix C(A.rows, A.cols);
    for(size_t i = 0; i < A.data.size() ;i++){
        C.data[i] = A.data[i] + B.data[i];
    }

    return C;
}

Matrix Matrix::sub(const Matrix &A, const Matrix &B){
    assert_dim_equal(A, B);

    Matrix C(A.rows, A.cols);
    for(size_t i = 0; i < A.data.size() ;i++){
        C.data[i] = A.data[i] - B.data[i];
    }

    return C;
}

Matrix Matrix::haamard_product(const Matrix &A, const Matrix &B){
    assert_dim_equal(A, B);

    Matrix C(A.rows, A.cols);
    for(size_t i = 0; i < A.data.size() ;i++){
        C.data[i] = A.data[i] * B.data[i];
    }

    return C;
}