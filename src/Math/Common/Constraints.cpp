#include "Constraints.hpp"

#include "Exponentials.hpp"

namespace E::M {
float Clamp(float value, float min, float max) {
    return std::clamp(value, min, max);
}

float SMax(float a, float b, float bias) {
    return (a + b + Sqrt(Pow(a - b, 2.0f) * bias)) / 2.0f;
}
} // namespace E::M
