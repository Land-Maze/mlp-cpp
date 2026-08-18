#pragma once
#include <lml/activation.hpp>
#include <lml/matrix.hpp>

namespace LML {
struct DenseLayer {
	Matrix z;
	Matrix W;
	Matrix b;
	ActivationType act;

	Matrix a_in;
	Matrix a_out;

	Matrix gradient;
	Matrix delta;
	Matrix dX;

	// activation derivative with z
	Matrix dZ;

	DenseLayer(size_t n_in, size_t n_out, ActivationType act);

	/// @brief Calculates W*a+b
	/// @param a
	/// @return W*a+b matrix reference
	const Matrix &forward_pass(const Matrix &a);

	/// @brief Calculates internal dW, delta
	/// @param d_next
	/// @return Calculated dX matrix reference
	const Matrix &backward_pass(const Matrix &d_next);

	void update_weights(const float learning_rate = 0.1f);
};
} // namespace LML
