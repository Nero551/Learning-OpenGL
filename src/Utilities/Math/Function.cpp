#include "Function.hpp"

float Function::Evaluate(const float x) const {
    return Func(x);
}

float Function::Derivative(const float x, const float dx) const {
    return Differentiate(dx).Evaluate(x);
}

Function Function::Differentiate(const float dx) const {
    auto derivative = [f = *this, dx](const float x) -> float {
        return (f(x + dx) - f(x)) / dx;
    };

    return derivative;
}

Function Function::Compose(const Function& g) const {
    auto func = [f = *this, g](const float x) -> float {
        return f(g(x));
    };
    return {func};
}

float Function::operator()(float x) const {
    return Evaluate(x);
}

Function Function::operator+(const Function& g) const {
    auto func = [f = *this, g](const float x) -> float {
        return f(x) + g(x);
    };

    return {func};
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
    auto func = [f = *this, scalar](float x) {
        return scalar * f(x);
    };

    return {func};
}
