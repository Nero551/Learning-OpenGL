#include "Function.hpp"

#include "MathUtils.hpp"

float Function::Evaluate(const float x) const {
    return Func(x);
}

float Function::Derivative(const float x, const float dx) const {
    return Differentiate(dx).Evaluate(x);
}

Function Function::Differentiate(const float dx) const {
    auto derivative = [f = *this, dx](const float x) -> float {
        const float dy = f(x + dx) - f(x);
        return dy / dx;
    };

    return derivative;
}

Function Function::Compose(const Function& g) const {
    return [f = *this, g](const float x) -> float {
        return f(g(x));
    };
}

float Function::InverseEvaluate(float y, float domainMin, float domainMax) const {
    float x = (domainMin + domainMax) / 2.0f;
    float value = Evaluate(x);

    while (!Math::NearlyEquals(domainMax, domainMin) && !Math::NearlyEquals(value, y)) {
        x = (domainMin + domainMax) / 2.0f;

        value = Evaluate(x);

        if (value < y) {
            domainMin = x;
        }
        else {
            domainMax = x;
        }
    }

    return (domainMin + domainMax) / 2.0f;
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

Function Function::operator*(const float scalar) const {
    return [f = *this, scalar](float x) {
        return scalar * f(x);
    };
}
