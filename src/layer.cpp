#include <lml/layer.hpp>
#include <lml/initializer.hpp>

using namespace LML;

Layer::Layer(size_t n_in, size_t n_out, ActivationType method)
: z(n_out, 1), W(n_out, n_in), b(n_out, 1), act(method), a(n_in, 1)
, dW(n_in, 1), delta(n_in, 1), dX(n_in, 1), dZ(n_out, 1)
{
    Initializer::glorot_uniform(this->W, n_in, n_out);
    Initializer::fill_zeros(this->b);
}

const Matrix& Layer::forward_pass(const Matrix &a_in)
{
    assert_dim(W, a_in);
    z = Matrix::mul(this->W, a_in);

    z = Matrix::add(z, b);

    Matrix a(z.rows, 1);
    Activation::apply(z, a, this->act);

    this->a = a;
    return this->z;
}

const Matrix& Layer::backward_pass(const Matrix& d_next){
    Activation::apply_derivative(z, dZ, this->act);
    this->delta = Matrix::haamard_product(d_next, dZ);
    dW = Matrix::mul_transposed_B(this->delta, this->a);
    dX = Matrix::mul_transposed_A(this->W, this->delta);
    return dX;
}

void Layer::update_weights(const float learning_rate){
    Matrix coeficient(W.rows, W.cols, learning_rate);
    this->W = Matrix::sub(W, Matrix::haamard_product(coeficient, dW));
}