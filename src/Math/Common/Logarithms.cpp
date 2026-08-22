#include "Logarithms.hpp"

#include <complex>

namespace E::M {
float Ln(const float x) {
    return std::log(x);
}

Complex Ln(const Complex& z) {
    Complex result;
    result.Real = Ln(z.Magnitude());
    result.Imaginary = z.Argument();

    return result;
}

float Log(const float base, const float x) {
    return Ln(x) / Ln(base);
}

Complex Log(const Complex& base, const Complex& z) {
    return Ln(z) / Ln(base);
}
} // namespace E::M
