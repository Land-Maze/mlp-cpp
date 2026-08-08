#include <catch2/catch_test_macros.hpp>
#include <lml/matrix.hpp>
#include <math.h>

TEST_CASE("Matrix Dimensions", "[matrix][dimensions]") {
    SECTION("Constructing matrix sets correct dimensions") {
        LML::Matrix m(2, 2);
        REQUIRE(m.rows == 2);
        REQUIRE(m.cols == 2);
        REQUIRE(m.data.size() == pow(2, 2));
    }

    SECTION("Default initialization fills with zeros") {
        LML::Matrix m(2, 2);
        for (size_t i = 0; i < m.rows; i++) {
            for (size_t j = 0; j < m.cols; j++) {
                REQUIRE(m(i, j) == 0.0f);
            }
        }
    }
}

TEST_CASE("Matrix Multiplication Correctness", "[matrix][multiplication]") {
    SECTION("Dimensions of multiplication result are correct") {
        LML::Matrix A(3, 2);
        LML::Matrix B(2, 5);

        LML::Matrix C = LML::Matrix::mul(A, B);

        REQUIRE(C.rows == 3);
        REQUIRE(C.cols == 5);
    }

    SECTION("Multiplication produces expected values") {
        LML::Matrix A(2, 2);
        LML::Matrix B(2, 2);

        A(0, 0) = 1;
        A(0, 1) = 2;
        A(1, 0) = 3;
        A(1, 1) = 4;

        B(0, 0) = 5;
        B(0, 1) = 6;
        B(1, 0) = 7;
        B(1, 1) = 8;

        LML::Matrix C = LML::Matrix::mul(A, B);
        REQUIRE(C(0, 0) == 19.0f);
        REQUIRE(C(0, 1) == 22.0f);
        REQUIRE(C(1, 0) == 43.0f);
        REQUIRE(C(1, 1) == 50.0f);
    }
}
