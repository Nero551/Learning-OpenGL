#include "Trigonometry.hpp"

#include "Comparison.hpp"
#include "Constants.hpp"
#include "Exponentials.hpp"

namespace E::M {
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
} // namespace E::M
