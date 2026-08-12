#pragma once
#include <lml/matrix.hpp>

namespace LML
{
    enum class ActivationType
    {
        Sigmoid
    };

    struct Activation
    {
        static void apply(const Matrix &Z, Matrix &A, ActivationType method);

        static void apply_derivative(const Matrix &A, Matrix &dZ, ActivationType method);
    };
}