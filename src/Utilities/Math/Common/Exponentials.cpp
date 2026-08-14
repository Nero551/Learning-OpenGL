#include "Exponentials.hpp"

namespace E::M {
float Pow(float x, float power) {
    return std::pow(x, power);
}

float Sqrt(float x) {
    return std::sqrt(x);
}

float Exp(float x) {
    return std::exp(x);
}
}