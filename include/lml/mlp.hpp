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

	Matrix squared_error(Matrix target);

  private:
	MLPCreateInfo m_metadata;
	std::vector<std::unique_ptr<Layer>> m_layers;
};
} // namespace LML
