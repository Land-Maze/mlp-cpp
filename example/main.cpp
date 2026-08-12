#include <iostream>
#include <lml/mlp.hpp>

using namespace LML;

int main() {
    MLPCreateInfo createInfo{
        .layer_sizes{{2,5},{5, 1}},
        .activation_function = ActivationType::Sigmoid,
        .learning_rate = 0.5f
    };

    MLP xor_mlp(createInfo);

    std::vector<std::pair<Matrix, Matrix>> dataset;
    for(size_t i = 0; i < 4; i++)
        dataset.push_back({Matrix(2,1), Matrix(1,1)});

    dataset[0].first.data = {1,0};
    dataset[0].second.data = {1};

    dataset[1].first.data = {0,1};
    dataset[1].second.data = {1};

    dataset[2].first.data = {1,1};
    dataset[2].second.data = {0};

    dataset[3].first.data = {0,0};
    dataset[3].second.data = {0};

    printf("Training phase\n");

    constexpr size_t EPOCH = 5000;

    for(size_t i = 0; i < EPOCH; i++){
        float mse = 0.0f;
        for(auto& entry : dataset){
            xor_mlp.forward(entry.first);
            xor_mlp.backward(entry.second);
            xor_mlp.update();
            mse = xor_mlp.mse(entry.second)(0,0);
        }
        if((i % 1000) == 0)
                printf("Epoch %zu, MSE %f\n", i, mse);
    }

    for(auto& entry : dataset){
        auto result = xor_mlp.forward(entry.first);
        printf("Input {%f, %f}, Output %f\n", entry.first(0,0), entry.first(1,0), result(0,0));
    }
}
