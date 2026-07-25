#include "Function.hpp"

float Function::Evaluate(const float x) const {
    return Func(x);
}

float Function::Derivative(const float x, const float dx) const {
    return (Evaluate(x + dx) - Evaluate(x)) / dx;
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
