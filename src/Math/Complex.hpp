#pragma once

namespace E::M {
struct Complex {
    float Real;
    float Imaginary;

    Complex();
    Complex(float real, float imaginary);
    static Complex FromPolar(float argument, float magnitude = 1);

    float MagnitudeSquared() const;
    float Magnitude() const;
    float Argument() const;
    Complex Conjugate() const;
    Complex Inverse() const;

    Complex operator-() const;

    Complex operator*(const Complex& b) const;
    Complex operator/(const Complex& b) const;
    Complex operator+(const Complex& b) const;
    Complex operator-(const Complex& b) const;

    Complex operator*(float scalar) const;
    Complex operator/(float scalar) const;
    Complex operator+(float scalar) const;
    Complex operator-(float scalar) const;
    friend Complex operator*(float scalar, const Complex& a);
    friend Complex operator/(float scalar, const Complex& a);
    friend Complex operator+(float scalar, const Complex& a);
    friend Complex operator-(float scalar, const Complex& a);

    friend std::ostream& operator<<(std::ostream& os, const Complex& complex);
};
} // namespace E::M
