#pragma once
#include "Complex.hpp"

namespace E::M {
Complex Pow(float x, const Complex& z);
Complex Pow(const Complex& z, float power);
Complex Pow(const Complex& z, const Complex& w);

Complex Sqrt(const Complex& z);


Complex Exp(const Complex& z);
} // namespace E::M
