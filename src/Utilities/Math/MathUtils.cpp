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

bool NearlyEquals(const float a, const float b, const float epsilon) {
    return std::abs(a - b) <= epsilon;
}
} // namespace E::M
