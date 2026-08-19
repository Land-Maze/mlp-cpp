#pragma once
#include <lml/activation.hpp>
#include <lml/matrix.hpp>

namespace LML {

struct Layer {
	Matrix W;
	Matrix gradient;
	Matrix a_out;

	Layer(Matrix W, Matrix gradient, Matrix a_out)
		: W(W), gradient(gradient), a_out(a_out) {};
	virtual ~Layer() = default;

	virtual const Matrix &forward_pass(const Matrix &a) = 0;
	virtual const Matrix &backward_pass(const Matrix &d_next) = 0;
};

struct DenseLayer : public Layer {
	Matrix z;
	Matrix b;
	ActivationType act;

	Matrix a_in;

	Matrix delta;
	Matrix dX;

	// activation derivative with z
	Matrix dZ;

	DenseLayer(size_t n_in, size_t n_out, ActivationType act);

	/// @brief Calculates W*a+b
	/// @param a
	/// @return W*a+b matrix reference
	const Matrix &forward_pass(const Matrix &a) override;

	/// @brief Calculates internal dW, delta
	/// @param d_next
	/// @return Calculated dX matrix reference
	const Matrix &backward_pass(const Matrix &d_next) override;

	void update_weights(const float learning_rate = 0.1f);
};
} // namespace LML
