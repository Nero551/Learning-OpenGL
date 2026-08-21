#pragma once

namespace E::M {
struct Complex {
    float Real;
    float Imaginary;

    Complex();
    Complex(float real, float imaginary);

    friend std::ostream& operator<<(std::ostream& os, const Complex& complex);
};
} // namespace E::M
