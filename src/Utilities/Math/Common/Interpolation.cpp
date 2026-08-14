#include "Exponentials.hpp"
#include "Interpolation.hpp"

namespace E::M {
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
}
