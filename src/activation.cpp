#include "lml/matrix.hpp"
#include <cassert>
#include <cmath>
#include <lml/activation.hpp>

using namespace LML;

constexpr float LeakyReLu_alpha_coefficient = 0.001f;

void Activation::apply(const Matrix &Z, Matrix &A, ActivationType method) {
	assert_dim_equal(Z, A);

	switch (method) {
	case ActivationType::Sigmoid:
		for (size_t i = 0; i < Z.data.size(); i++) {
			A.data[i] = 1.0f / (1.0f + std::exp(-1.0f * Z.data[i]));
		}
		break;
	case LML::ActivationType::LeakyReLu:
		for (size_t i = 0; i < Z.data.size(); i++) {
			A.data[i] = std::max(Z.data[i], LeakyReLu_alpha_coefficient * Z.data[i]);
		}
		break;
	default:
		assert(false && "Unsupported activation type");
		break;
	}
}

void Activation::apply_derivative(const Matrix &A, Matrix &dZ, Matrix &X, ActivationType method) {
	assert_dim_equal(A, dZ);
	assert_dim_equal(dZ, X);

	switch (method) {
	case ActivationType::Sigmoid:
		for (size_t i = 0; i < A.data.size(); i++) {
			dZ.data[i] = A.data[i] * (1.0f - A.data[i]);
		}
		break;
	case ActivationType::LeakyReLu:
		for (size_t i = 0; i < A.data.size(); i++) {
			dZ.data[i] = X.data[i] > 0.0f ? 1 : LeakyReLu_alpha_coefficient;
		}
		break;
	default:
		assert(false && "Unsupported activation type");
		break;
	}
}
