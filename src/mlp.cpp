#include <lml/mlp.hpp>
#include <memory>

using namespace LML;

MLP::MLP(MLPCreateInfo createInfo) : m_metadata(createInfo) {
	for (size_t i = 0; i < m_metadata.layer_sizes.size(); i++) {
		m_layers.push_back(std::make_unique<DenseLayer>(
			m_metadata.layer_sizes[i].first, m_metadata.layer_sizes[i].second,
			m_metadata.activation_function));
	}
}

Matrix MLP::forward(Matrix input) {
	assert(m_layers[0]->W.cols == input.data.size());

	Matrix a = this->m_layers[0]->forward_pass(input);
	for (size_t i = 1; i < this->m_metadata.layer_sizes.size(); i++) {
		assert(a.data.size() == this->m_layers[i]->W.cols);
		a = this->m_layers[i]->forward_pass(a);
	}
	return a;
}

Matrix MLP::squared_error(Matrix target) {
	assert_dim_equal(m_layers.back()->a_out, target);

	Matrix error = Matrix::sub(m_layers.back()->a_out, target);
	Matrix squared_error = Matrix::mul(error, error);

	Matrix coef(target.rows, target.cols, 0.5f);
	return Matrix::haamard_product(coef, squared_error);
}

void MLP::backward(Matrix target) {
	assert_dim_equal(m_layers.back()->a_out, target);

	Matrix dX = Matrix::sub(m_layers.back()->a_out, target);
	for (size_t i = m_layers.size(); i-- > 0;) {
		dX = m_layers[i]->backward_pass(dX);
	}
}
