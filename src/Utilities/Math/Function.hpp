#pragma once

namespace E::M {
template <typename T>
concept Func = std::invocable<T, float> && std::same_as<std::invoke_result_t<T, float>, float>;

struct Function {
    template <Func T> requires Func<T> && (!std::same_as<std::remove_cvref_t<T>, Function>)
    Function(T&& f) : Func(std::forward<T>(f)) {}

    [[nodiscard]] float Evaluate(float x) const;
    [[nodiscard]] Function Compose(const Function& g) const;

    //! its hella buggy but kinda works
    [[nodiscard]] float InverseEvaluate(float y, float domainMin = 0, float domainMax = 10) const;
    //! its hella buggy but kinda works
    [[nodiscard]] Function Inverse(float min, float max) const;

    [[nodiscard]] float Derivative(float x, float dx = 0.001f) const;
    [[nodiscard]] Function Differentiate(float dx = 0.001f) const;

    [[nodiscard]] Function Integrate(float a, float dx = 0.001f) const;
    [[nodiscard]] float Integral(float a, float b, float dx = 0.001f) const;


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
} // namespace E::M
