#pragma once
#include <lml/layer.hpp>
#include <vector>
#include <memory>

namespace LML
{

    struct MLPCreateInfo{
        size_t input_n;

        std::vector<std::pair<size_t, size_t>> layer_sizes;

        size_t output_n;

        ActivationType activation_function;

        float learning_rate;
    };

    class MLP{
        public:
        MLP(MLPCreateInfo createInfo);

        Matrix forward(Matrix input);
        void backward(Matrix target);
        void update();
        
        Matrix mse(Matrix target);

        private:
        MLPCreateInfo m_metadata;
        std::vector<Layer> m_layers;
    };
}
