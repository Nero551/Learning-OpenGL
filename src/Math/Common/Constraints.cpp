#include "Constraints.hpp"

#include "Exponentials.hpp"

namespace E::M {
float Clamp(const float value, const float min, const float max) {
    return std::clamp(value, min, max);
}

float SMax(const float a, const float b, const float bias) {
    return (a + b + Sqrt(Pow(a - b, 2.0f) * bias)) / 2.0f;
}
} // namespace E::M
