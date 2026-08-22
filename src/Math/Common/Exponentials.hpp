#pragma once
#include "Math/Complex.hpp"

namespace E::M {
float Pow(float x, float power);
Complex Pow(float x, const Complex& z);
Complex Pow(const Complex& z, float power);
Complex Pow(const Complex& z, const Complex& w);

float Sqrt(float x);
Complex Sqrt(const Complex& z);

float Exp(float x);
Complex Exp(const Complex& z);

float Factorial(int x);
} // namespace E::M
