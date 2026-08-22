#pragma once
#include "Math/Complex.hpp"

namespace E::M {
inline constexpr float EPSILON = 1e-5f;
inline constexpr float E = std::numbers::e_v<float>;
inline constexpr float PI = std::numbers::pi_v<float>;
inline constexpr float TAU = PI * 2.0f;
inline Complex I{ 0, 1 };
} // namespace E::M
