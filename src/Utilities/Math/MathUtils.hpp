#pragma once

namespace Math {
    inline constexpr float EPSILON = 1e-5f;
    inline constexpr float E = std::numbers::e_v<float>;
    inline constexpr float PI = std::numbers::pi_v<float>;
    inline constexpr float TAU = PI * 2.0f;

    float Rad(float deg);
    float Deg(float rad);

    bool NearlyEquals(float a, float b, float epsilon = EPSILON);
} // namespace Math
