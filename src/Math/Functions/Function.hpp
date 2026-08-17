#pragma once
#include "DifferentiationMethod.hpp"
#include "IntegrationMethod.hpp"

namespace E::M {
template <typename T>
concept Func = std::invocable<T, float> && std::same_as<std::invoke_result_t<T, float>, float>;

struct Function {
    template <Func T>
        requires Func<T> && (!std::same_as<std::remove_cvref_t<T>, Function>)
    Function(T&& f) : Func(std::forward<T>(f)) {
    }

    [[nodiscard]] float Evaluate(float x) const;
    [[nodiscard]] Function Compose(const Function& g) const;

    //! its hella buggy but kinda works
    [[nodiscard]] float InverseEvaluate(float y, float domainMin = 0, float domainMax = 10) const;
    //! its hella buggy but kinda works
    [[nodiscard]] Function Inverse(float min, float max) const;

    [[nodiscard]] float Derivative(
        float x, float dx = 0.001f, DifferentiationMethod method = DifferentiationMethod::Central) const;
    [[nodiscard]] Function Differentiate(float dx = 0.001f, DifferentiationMethod method = DifferentiationMethod::Central) const;

    /** @brief doesn't work if the lower bound (a) is not 0 */
    [[nodiscard]] Function Integrate(
        float lowerBound, float dx = 0.001f, IntegrationMethod method = IntegrationMethod::Midpoint) const;
    /** @brief doesn't work if the lower bound (a) is not 0 */
    [[nodiscard]] float Integral(
        float lowerBound, float upperBound, float dx = 0.001f, IntegrationMethod method = IntegrationMethod::Midpoint) const;

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
