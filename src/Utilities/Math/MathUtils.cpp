#include "MathUtils.hpp"


float Math::Rad(const float deg) {
    return deg * PI / 180;
}

float Math::Deg(const float rad) {
    return rad * 180 / PI;
}

bool Math::NearlyEquals(const float a, const float b, const float epsilon) {
    return std::abs(a - b) < epsilon;
}
