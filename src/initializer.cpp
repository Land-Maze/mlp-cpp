#include <lml/initializer.hpp>
#include <cmath>

using namespace LML;

std::mt19937& Initializer::get_rng(){
    static std::mt19937 gen(1337);
        return gen;
}

void Initializer::glorot_uniform(Matrix& W, size_t n_in, size_t n_out){
    float stddev = std::sqrt(6.0f / static_cast<float>(n_in + n_out));
    std::uniform_real_distribution<float> dist(-stddev, stddev);
    for (auto& val : W.data) {
        val = dist(get_rng());
    }
}

void Initializer::he_normal(Matrix& W, size_t n_in){
    float stddev = std::sqrt(2.0f / static_cast<float>(n_in));
    std::normal_distribution<float> dist(0.0f, stddev);
        for (auto& val : W.data) {
            val = dist(get_rng());
    }
}

void Initializer::fill_zeros(Matrix& M) {
        std::fill(M.data.begin(), M.data.end(), 0.0f);
}