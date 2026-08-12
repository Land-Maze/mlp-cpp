#pragma once

#include <random>
#include <lml/matrix.hpp>

namespace LML{
    struct Initializer{
        static std::mt19937& get_rng();

        static void glorot_uniform(Matrix& W, size_t n_in, size_t n_out);
        static void he_normal(Matrix& W, size_t n_in);
        static void fill_zeros(Matrix& M);
    };
}