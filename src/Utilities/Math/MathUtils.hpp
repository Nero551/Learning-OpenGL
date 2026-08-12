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
float Sin(float rad);

float Pow(float x, float power);
float Sqrt(float x);

float Exp(float x);
float Ln(float x);
float Log(float base, float x);

float Clamp(float value, float min, float max);

float Lerp(float a, float b, float t);
float EaseInQuad(float t);
float EaseOutQuad(float t);
float EaseInOutQuad(float t);

float EaseInCubic(float t);
float EaseOutCubic(float t);
float EaseInOutCubic(float t);

bool NearlyEquals(float a, float b, float epsilon = EPSILON);
} // namespace E::M
