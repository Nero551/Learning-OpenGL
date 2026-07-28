#pragma once

namespace Math {
    inline constexpr float EPSILON = 1e-5f;
    inline constexpr float E = std::numbers::e_v<float>;
    inline constexpr float PI = std::numbers::pi_v<float>;
    inline constexpr float TAU = PI * 2.0f;

    float Rad(float deg);
    float Deg(float rad);

    float DSin(float deg);
    float DCos(float deg);
    float DTan(float deg);

    float Pow(float x, float power);
    float Sqrt(float x);

    float Ln(float x);
    float Log(float base, float x);

    bool NearlyEquals(float a, float b, float epsilon = EPSILON);
} // namespace Math
