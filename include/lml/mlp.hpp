#pragma once
#include <lml/layer.hpp>
#include <memory>
#include <vector>

namespace LML {

struct MLPCreateInfo {
	std::vector<std::pair<size_t, size_t>> layer_sizes;

	ActivationType activation_function;

	float learning_rate;
};

class MLP {
  public:
	MLP(MLPCreateInfo createInfo);

	Matrix forward(Matrix input);
	void backward(Matrix target);
	void update();

	Matrix squared_error(Matrix target);

  private:
	MLPCreateInfo m_metadata;
	std::vector<DenseLayer> m_layers;
};
} // namespace LML
