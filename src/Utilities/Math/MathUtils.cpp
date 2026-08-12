#include "MathUtils.hpp"

#include "Utilities/Logger.hpp"


namespace E::M {
static std::mt19937 rng(std::random_device{}());

float Random(float min, float max) {
    std::uniform_real_distribution distribution(min, max);
    return distribution(rng);
}

int Random(int min, int max) {
    std::uniform_int_distribution distribution(min, max);
    return distribution(rng);
}

float RandomGaussian(float mean, float standardDeviation) {
    std::normal_distribution distribution(mean, standardDeviation);
    return distribution(rng);
}

float Rad(const float deg) {
    return deg * PI / 180;
}

float Deg(const float rad) {
    return rad * 180 / PI;
}

float DSin(float deg) {
    return std::sin(Rad(deg));
}

float DCos(float deg) {
    return std::cos(Rad(deg));
}

float DTan(float deg) {
    return std::tan(Rad(deg));
}

float Sin(float rad) {
    float angle = Rad(90);
    float s = 1;
    float c = 0;

    while (!NearlyEquals(angle, rad, 0.2)) {
        if (angle > rad) {
            s = Sqrt((1 - c) / 2);
            c = Sqrt((1 + c) / 2);
            angle /= 2;
        }
        else {
            s = 2 * s * c;
            c = Pow(c, 2) - Pow(s, 2);
            angle *= 2;
        }
    }
    return s;
}

float Pow(float x, float power) {
    return std::pow(x, power);
}

float Sqrt(float x) {
    return std::sqrt(x);
}

float Exp(float x) {
    return std::exp(x);
}

float Ln(float x) {
    return std::log(x);
}

float Log(float base, float x) {
    return Ln(x) / Ln(base);
}

float Clamp(float value, float min, float max) {
    return std::clamp(value, min, max);
}

float Lerp(float a, float b, float t) {
    return a + (b - a) * t;
}

float EaseInQuad(float t) {
    return t * t;
}

float EaseOutQuad(float t) {
    return 1 - Pow((1 - t), 2);
}

float EaseInOutQuad(float t) {
    if (t < 0.5f)
        return 0.5f * EaseInQuad(t * 2.0f);

    return 0.5f + 0.5f * EaseOutQuad((t - 0.5f) * 2.0f);
}

float EaseInCubic(float t) {
    return t * t * t;
}

float EaseOutCubic(float t) {
    return 1 - Pow((1 - t), 3);
}

float EaseInOutCubic(float t) {
    if (t < 0.5f)
        return 4 * EaseInCubic(t);

    return 0.5f + 0.5f * EaseOutCubic((t - 0.5f) * 2.0f);
}

bool NearlyEquals(const float a, const float b, const float epsilon) {
    return std::abs(a - b) <= epsilon;
}
} // namespace E::M
