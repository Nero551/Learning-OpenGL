#include "Exponentials.hpp"

#include "Logarithms.hpp"

namespace E::M {
float Pow(const float x, const float power) {
    return std::pow(x, power);
}

Complex Pow(float x, Complex complexPower) {
    Complex result;

    float magnitude = Pow(x, complexPower.Real);
    float theta = complexPower.Imaginary * Ln(x);

    result.Real = magnitude * std::cos(theta);
    result.Imaginary = magnitude * std::sin(theta);

    return result;
}

float Sqrt(const float x) {
    return std::sqrt(x);
}

float Exp(const float x) {
    return std::exp(x);
}

float Factorial(int x) {
    float result = 1.0f;
    for (int i = x; i > 0; i--) {
        result *= static_cast<float>(i);
    }
    return result;
}
} // namespace E::M
