#pragma once
#include "Math/Complex.hpp"

namespace E::M {
float Pow(float x, float power);
Complex Pow(float x, Complex complexPower);

float Sqrt(float x);

float Exp(float x);

float Factorial(int x);
} // namespace E::M
