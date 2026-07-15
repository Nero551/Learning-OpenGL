#include "MathUtils.hpp"

#include <limits>
#include <numbers>

float Math::Radians(float deg) { return deg * std::numbers::pi / 180; }

float Math::Degrees(float rad) { return rad * 180 / std::numbers::pi; }

bool Math::NearlyEquals(float a, float b, float epsilon) { return std::abs(a - b) < epsilon; }
