#include <lml/initializer.hpp>
#include <lml/layer.hpp>

using namespace LML;

DenseLayer::DenseLayer(size_t n_in, size_t n_out, ActivationType method)
	: z(n_out, 1), W(n_out, n_in), b(n_out, 1), act(method), a_in(n_in, 1), a_out(n_out, 1), gradient(n_out, n_in),
	  delta(n_out, 1), dX(n_in, 1), dZ(n_out, 1) {
	Initializer::glorot_uniform(this->W, n_in, n_out);
	Initializer::fill_zeros(this->b);
}

const Matrix &DenseLayer::forward_pass(const Matrix &a_in) {
	assert_dim(W, a_in);
	this->z = Matrix::mul(this->W, a_in);

	this->z = Matrix::add(z, b);

	Activation::apply(z, this->a_out, this->act);

	this->a_in = a_in;
	return this->a_out;
}

const Matrix &DenseLayer::backward_pass(const Matrix &d_next) {
	Activation::apply_derivative(a_out, dZ, this->z, this->act);
	this->delta = Matrix::haamard_product(d_next, dZ);
	gradient = Matrix::mul_transposed_B(this->delta, this->a_in);
	dX = Matrix::mul_transposed_A(this->W, this->delta);
	return dX;
}

void DenseLayer::update_weights(const float learning_rate) {
	for (size_t i = 0; i < W.data.size(); ++i) {
		W.data[i] -= learning_rate * gradient.data[i];
	}
	for (size_t i = 0; i < b.data.size(); ++i) {
		b.data[i] -= learning_rate * delta.data[i];
	}
}
