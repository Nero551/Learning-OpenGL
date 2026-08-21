#include "Complex.hpp"

namespace E::M {
Complex::Complex() : Real(0), Imaginary(0) {
}
Complex::Complex(float real, float imaginary) : Real(real), Imaginary(imaginary) {
}

std::ostream& operator<<(std::ostream& os, const Complex& complex) {
    os << complex.Real;
    if (complex.Imaginary < 0) {
        os << " - " << -complex.Imaginary << "i";
    }
    else {
        os << " + " << complex.Imaginary << "i";
    }

    return os;
}
} // namespace E::M
