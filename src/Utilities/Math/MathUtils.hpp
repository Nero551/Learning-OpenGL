#pragma once

namespace E::M {
inline constexpr float EPSILON = 1e-5f;
inline constexpr float E = std::numbers::e_v<float>;
inline constexpr float PI = std::numbers::pi_v<float>;
inline constexpr float TAU = PI * 2.0f;

float Random(float min = 0.0f, float max = 1.0f);
int Random(int min, int max);
float RandomGaussian(float mean, float standardDeviation);

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
} // namespace E::M
