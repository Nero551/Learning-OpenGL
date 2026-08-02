#pragma once
#include <functional>

template <typename T>
concept F = std::invocable<T, float> && std::same_as<std::invoke_result_t<T, float>, float>;

struct Function {
    template <F T> requires F<T> && (!std::same_as<std::remove_cvref_t<T>, Function>)
    Function(T&& f) : Func(std::forward<T>(f)) {}

    [[nodiscard]] float Evaluate(float x) const;
    [[nodiscard]] float InverseEvaluate(float y, float domainMin = 0, float domainMax = 10) const;
    [[nodiscard]] Function Inverse(float min, float max) const;
    [[nodiscard]] float Derivative(float x, float dx = 0.001f) const;
    [[nodiscard]] Function Differentiate(float dx = 0.001f) const;
    [[nodiscard]] Function Compose(const Function& g) const;

    float operator()(float x) const;
    Function operator()(const Function& g) const;
    Function operator+(const Function& g) const;
    Function operator-(const Function& g) const;
    Function operator*(const Function& g) const;
    Function operator/(const Function& g) const;
    Function operator-() const;

    Function operator+(float scalar) const;
    Function operator-(float scalar) const;
    Function operator*(float scalar) const;
    Function operator/(float scalar) const;

    friend Function operator+(float scalar, const Function& f);
    friend Function operator-(float scalar, const Function& f);
    friend Function operator*(float scalar, const Function& f);
    friend Function operator/(float scalar, const Function& f);

private:
    std::function<float(float)> Func;
};
