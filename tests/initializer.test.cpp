#include <catch2/catch_test_macros.hpp>
#include <lml/initializer.hpp>
#include <lml/matrix.hpp>
#include <cmath>

TEST_CASE("Initializer Fill Zeros", "[initializer][zeros]") {
    LML::Matrix m(4, 4);
    for (size_t i = 0; i < m.rows; i++) {
        for (size_t j = 0; j < m.cols; j++) {
            m(i, j) = static_cast<float>(i + j + 1);
        }
    }

    LML::Initializer::fill_zeros(m);

    for (size_t i = 0; i < m.rows; i++) {
        for (size_t j = 0; j < m.cols; j++) {
            REQUIRE(m(i, j) == 0.0f);
        }
    }
}

TEST_CASE("Initializer Glorot Uniform", "[initializer][glorot]") {
    size_t n_in = 10;
    size_t n_out = 20;
    LML::Matrix W(n_in, n_out);

    LML::Initializer::glorot_uniform(W, n_in, n_out);

    float limit = std::sqrt(6.0f / static_cast<float>(n_in + n_out));

    bool has_nonzero = false;
    for (float val : W.data) {
        REQUIRE(val >= -limit);
        REQUIRE(val <= limit);
        if (val != 0.0f) {
            has_nonzero = true;
        }
    }
    REQUIRE(has_nonzero);
}

TEST_CASE("Initializer He Normal", "[initializer][he]") {
    size_t n_in = 16;
    size_t n_out = 16;
    LML::Matrix W(n_in, n_out);

    LML::Initializer::he_normal(W, n_in);

    bool has_nonzero = false;
    for (float val : W.data) {
        if (val != 0.0f) {
            has_nonzero = true;
        }
    }
    REQUIRE(has_nonzero);
}

TEST_CASE("Initializer RNG Generator", "[initializer][rng]") {
    std::mt19937& rng1 = LML::Initializer::get_rng();
    std::mt19937& rng2 = LML::Initializer::get_rng();
    REQUIRE(&rng1 == &rng2);
}
