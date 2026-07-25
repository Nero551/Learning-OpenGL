#pragma once
#include <functional>

template <typename T>
concept F = std::invocable<T, float> && std::same_as<std::invoke_result_t<T, float>, float>;

struct Function {
    template <F T> requires F<T> && (!std::same_as<std::remove_cvref_t<T>, Function>)
    Function(T&& f) : Func(std::forward<T>(f)) {}

    float Evaluate(float x) const;
    float Derivative(float x, float dx = 1e-5f) const;
    Function Compose(const Function& g) const;

    float operator()(float x) const;
    Function operator+(const Function& g) const;
    Function operator-(const Function& g) const;
    Function operator*(const Function& g) const;
    Function operator/(const Function& g) const;

private:
    std::function<float(float)> Func;
};
