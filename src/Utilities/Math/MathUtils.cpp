#include "MathUtils.hpp"

#include <numbers>

float Math::Radians(float deg) {
    return deg * static_cast<float>(std::numbers::pi / 180);
}

float Math::Degrees(float rad) {
    return rad * static_cast<float>(180 / std::numbers::pi);
}

bool Math::NearlyEquals(float a, float b, float epsilon) {
    return std::abs(a - b) < epsilon;
}
