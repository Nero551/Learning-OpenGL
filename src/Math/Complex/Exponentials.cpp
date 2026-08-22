#include "Exponentials.hpp"
#include "Logarithms.hpp"
#include "Math/Common/Exponentials.hpp"
#include "Math/Common/Logarithms.hpp"

namespace E::M {
Complex Pow(float x, const Complex& z) {
    Complex result;

    float magnitude = Pow(x, z.Real);
    float theta = z.Imaginary * Ln(x);

    result.Real = magnitude * std::cos(theta);
    result.Imaginary = magnitude * std::sin(theta);

    return result;
}

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

Complex Sqrt(const Complex& z) {
    return Pow(z, 1 / 2);
}

Complex Exp(const Complex& z) {
    return Pow(E, z);
}
} // namespace E::M
