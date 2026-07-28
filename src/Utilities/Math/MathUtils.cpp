#include "MathUtils.hpp"


float Math::Rad(const float deg) {
    return deg * PI / 180;
}

float Math::Deg(const float rad) {
    return rad * 180 / PI;
}

float Math::DSin(float deg) {
    return std::sin(Rad(deg));
}

float Math::DCos(float deg) {
    return std::cos(Rad(deg));
}

float Math::DTan(float deg) {
    return std::tan(Rad(deg));
}

float Math::Pow(float x, float power) {
    return std::pow(x, power);
}

float Math::Sqrt(float x) {
    return std::sqrt(x);
}

float Math::Ln(float x) {
    return std::log(x);
}

float Math::Log(float base, float x) {
    return Ln(x) / Ln(base);
}

bool Math::NearlyEquals(const float a, const float b, const float epsilon) {
    return std::abs(a - b) <= epsilon;
}
