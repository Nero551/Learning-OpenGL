#pragma once
#include "Math/Complex.hpp"

namespace E::M {
float Ln(float x);
Complex Ln(const Complex& z);
float Log(float base, float x);
Complex Log(const Complex& base, const Complex& z);
} // namespace E::M
