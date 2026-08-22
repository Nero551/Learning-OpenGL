#include "Exponentials.hpp"

#include "Logarithms.hpp"
#include "Utilities/Logger.hpp"

namespace E::M {
float Pow(const float x, const float power) {
    return std::pow(x, power);
}

Complex Pow(float x, const Complex& z) {
    Complex result;

    float magnitude = Pow(x, z.Real);
    float theta = z.Imaginary * Ln(x);

    result.Real = magnitude * std::cos(theta);
    result.Imaginary = magnitude * std::sin(theta);

    return result;
}

// TODO- do complex exponential z^w where z and w are complex numbers

Complex Pow(const Complex& z, float power) {
    Complex result;

    float magnitude = Pow(z.Magnitude(), power);
    float theta = z.Argument() * power;

    result.Real = magnitude * std::cos(theta);
    result.Imaginary = magnitude * std::sin(theta);
    return result;
}

Complex Pow(const Complex& z, const Complex& w) {
    return Exp(w * Ln(z));
}

float Sqrt(const float x) {
    return std::sqrt(x);
}

Complex Sqrt(const Complex& z) {
    return Pow(z, 1 / 2);
}

float Exp(const float x) {
    return std::exp(x);
}

Complex Exp(const Complex& z) {
    return Pow(E, z);
}

float Factorial(int x) {
    if (x < 0)
        U::Logger::Error("Factorial requires a non-negative integer");

    float result = 1.0f;

    for (int i = x; i > 0; i--)
        result *= static_cast<float>(i);

    return result;
}
} // namespace E::M
