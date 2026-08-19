#include "Exponentials.hpp"

namespace E::M {
float Pow(const float x, const float power) {
    return std::pow(x, power);
}

float Sqrt(const float x) {
    return std::sqrt(x);
}

float Exp(const float x) {
    return std::exp(x);
}
} // namespace E::M
