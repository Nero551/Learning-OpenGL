module;

#include <numbers>

export module MathUtils;

export namespace Math {
constexpr float EPSILONF = 1e-6f;
constexpr double EPSILOND = 1e-9;

float DegToRad(float deg);
float RadToDeg(float rad);
} // namespace Math

float Math::DegToRad(float deg) { return deg * std::numbers::pi / 180; }
float Math::RadToDeg(float rad) { return rad * 180 / std::numbers::pi; }
