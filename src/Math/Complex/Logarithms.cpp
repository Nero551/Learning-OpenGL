#include "Logarithms.hpp"
#include "Math/Common/Logarithms.hpp"

namespace E::M {
Complex Ln(const Complex& z) {
    Complex result;
    result.Real = Ln(z.Magnitude());
    result.Imaginary = z.Argument();

    return result;
}

Complex Log(const Complex& base, const Complex& z) {
    return Ln(z) / Ln(base);
}
} // namespace E::M
