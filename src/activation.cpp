#include <lml/activation.hpp>
#include <cmath>
#include <cassert>

using namespace LML;

void Activation::apply(const Matrix &Z, Matrix &A, ActivationType method)
{
    assert_dim_equal(Z, A);

    switch (method)
    {
    case ActivationType::Sigmoid:
        for (size_t i = 0; i < Z.data.size(); i++)
        {
            A.data[i] = 1.0f / (1.0f + std::exp(-1.0f * Z.data[i]));
        }
        break;

    default:
        assert(false && "Unsupported activation type");
        break;
    }
}

void Activation::apply_derivative(const Matrix &A, Matrix &dZ, ActivationType method)
{
    assert_dim_equal(A, dZ);

    switch (method)
    {
    case ActivationType::Sigmoid:
        for (size_t i = 0; i < A.data.size(); i++)
        {
            dZ.data[i] = A.data[i] * (1.0f - A.data[i]);
        }
        break;
    default:
        assert(false && "Unsupported activation type");
        break;
    }
}
