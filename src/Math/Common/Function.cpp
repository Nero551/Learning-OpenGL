#include "Function.hpp"

#include "Comparison.hpp"
#include "Utilities/Logger.hpp"

namespace E::M {
float Function::Evaluate(const float x) const {
    return Func(x);
}

Function Function::Differentiate(const float dx) const {
    auto derivative = [f = *this, dx](const float x) -> float {
        float h = dx * std::max(1.0f, std::abs(x));
        return (f(x + h) - f(x - h)) / (2.0f * h);
    };

    return derivative;
}

float Function::Derivative(const float x, const float dx) const {
    return Differentiate(dx).Evaluate(x);
}

Function Function::Compose(const Function& g) const {
    return [f = *this, g](const float x) -> float {
        return f(g(x));
    };
}

Function Function::Integrate(float lowerBound, float dx) const {
    return [f = *this, lowerBound, dx](float upperBound) {
        float result = 0.0f;
        for (float x = lowerBound; x < upperBound; x += dx) {
            float midpoint = x + dx / 2.0f;
            result += f(midpoint) * dx;
        }
        return result;
    };
}

float Function::Integral(float lowerBound, float upperBound, float dx) const {
    return Integrate(lowerBound, dx).Evaluate(upperBound);
}

float Function::InverseEvaluate(float y, float domainMin, float domainMax) const {
    float x = 0;
    while (!NearlyEquals(domainMax, domainMin)) {
        x = (domainMin + domainMax) / 2.0f;

        float value = Evaluate(x);

        if (value < y) {
            domainMin = x;
        }
        else {
            domainMax = x;
        }
    }

    return x;
}

Function Function::Inverse(float min, float max) const {
    return [f = *this, min, max](float y) {
        return f.InverseEvaluate(y, min, max);
    };
}

float Function::operator()(float x) const {
    return Evaluate(x);
}

Function Function::operator()(const Function& g) const {
    return Compose(g);
}

Function Function::operator+(const Function& g) const {
    return [f = *this, g](const float x) -> float {
        return f(x) + g(x);
    };
}

Function Function::operator-(const Function& g) const {
    return [f = *this, g](float x) {
        return f(x) - g(x);
    };
}

Function Function::operator*(const Function& g) const {
    return [f = *this, g](float x) {
        return f(x) * g(x);
    };
}

Function Function::operator/(const Function& g) const {
    return [f = *this, g](float x) {
        return f(x) / g(x);
    };
}

Function Function::operator-() const {
    return [f = *this](float x) {
        return -f(x);
    };
}

Function Function::operator+(float scalar) const {
    return [f = *this, scalar](const float x) -> float {
        return f(x) + scalar;
    };
}

Function Function::operator-(float scalar) const {
    return [f = *this, scalar](const float x) -> float {
        return f(x) - scalar;
    };
}

Function Function::operator/(float scalar) const {
    return [f = *this, scalar](const float x) -> float {
        return f(x) / scalar;
    };
}

Function Function::operator*(const float scalar) const {
    return [f = *this, scalar](float x) {
        return f(x) * scalar;
    };
}

Function operator+(float scalar, const Function& f) {
    return f + scalar;
}

Function operator-(float scalar, const Function& f) {
    return [f, scalar](float x) {
        return scalar - f(x);
    };
}

Function operator*(float scalar, const Function& f) {
    return f * scalar;
}

Function operator/(float scalar, const Function& f) {
    return [f, scalar](float x) {
        return scalar / f(x);
    };
}
} // namespace E::M
