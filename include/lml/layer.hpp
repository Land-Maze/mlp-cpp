#pragma once
#include <lml/matrix.hpp>
#include <lml/activation.hpp>

namespace LML{
    struct Layer{
        Matrix z;
        Matrix W;
        Matrix b;
        ActivationType act;

        Matrix a;

        Matrix dW;
        Matrix delta;
        Matrix dX;
        Matrix dZ;

        Layer(size_t n_in, size_t n_out, ActivationType act);

        /// @brief Calculates W*a+b
        /// @param a 
        /// @return W*a+b matrix reference
        const Matrix& forward_pass(const Matrix& a);
    

        /// @brief Calculates internal dW, delta
        /// @param d_next 
        /// @return Calculated dX matrix reference
        const Matrix& backward_pass(const Matrix& d_next);

        void update_weights(const float learning_rate = 0.1f);
    };
}