#include "Function.hpp"

#include "../Common/Comparison.hpp"
#include "Utilities/Logger.hpp"

namespace E::M {
float Function::Evaluate(const float x) const {
    return Func(x);
}

Function Function::Differentiate(const float dx, DifferentiationMethod method) const {
    auto derivative = [f = *this, dx, method](const float x) -> float {
        const float h = dx * std::max(1.0f, std::abs(x));
        switch (method) {
        case DifferentiationMethod::Central:
            return (f(x + h) - f(x - h)) / (2.0f * h);

        case DifferentiationMethod::Forward:
            return (f(x + h) - f(x)) / h;

        case DifferentiationMethod::Backward:
            return (f(x) - f(x - h)) / h;

        default:
            U::Logger::Fatal("Invalid Differentiation Method");
        }
    };

    return derivative;
}

float Function::Derivative(const float x, const float dx, DifferentiationMethod method) const {
    return Differentiate(dx, method).Evaluate(x);
}

Function Function::Compose(const Function& g) const {
    return [f = *this, g](const float x) -> float { return f(g(x)); };
}

Function Function::Integrate(float lowerBound, float dx, IntegrationMethod method) const {
    return [f = *this, lowerBound, dx, method](float upperBound) {
        float result = 0.0f;

        for (float x = lowerBound; x < upperBound; x += dx) {
            const float width = std::min(dx, upperBound - x);

            switch (method) {
            case IntegrationMethod::Midpoint:
                result += f(x + width / 2.0f) * width;
                break;

            case IntegrationMethod::Right:
                result += f(x + width) * width;
                break;

            case IntegrationMethod::Left:
                result += f(x) * width;
                break;

            case IntegrationMethod::Trapezoid:
                result += ((f(x) + f(x + width)) / 2.0f) * width;
                break;

            default:
                U::Logger::Fatal("Invalid Integration Method");
            }
        }

        return result;
    };
}

float Function::Integral(float lowerBound, float upperBound, float dx, IntegrationMethod method) const {
    return Integrate(lowerBound, dx, method).Evaluate(upperBound);
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

Function Function::Inverse(float domainMin, float domainMax) const {
    return [f = *this, domainMin, domainMax](float y) { return f.InverseEvaluate(y, domainMin, domainMax); };
}

float Function::operator()(float x) const {
    return Evaluate(x);
}

Function Function::operator()(const Function& g) const {
    return Compose(g);
}

Function Function::operator+(const Function& g) const {
    return [f = *this, g](const float x) -> float { return f(x) + g(x); };
}

Function Function::operator-(const Function& g) const {
    return [f = *this, g](float x) { return f(x) - g(x); };
}

Function Function::operator*(const Function& g) const {
    return [f = *this, g](float x) { return f(x) * g(x); };
}

Function Function::operator/(const Function& g) const {
    return [f = *this, g](float x) { return f(x) / g(x); };
}

Function Function::operator-() const {
    return [f = *this](float x) { return -f(x); };
}

Function Function::operator+(float scalar) const {
    return [f = *this, scalar](const float x) -> float { return f(x) + scalar; };
}

Function Function::operator-(float scalar) const {
    return [f = *this, scalar](const float x) -> float { return f(x) - scalar; };
}

Function Function::operator/(float scalar) const {
    return [f = *this, scalar](const float x) -> float { return f(x) / scalar; };
}

Function Function::operator*(const float scalar) const {
    return [f = *this, scalar](float x) { return f(x) * scalar; };
}

Function operator+(float scalar, const Function& f) {
    return f + scalar;
}

Function operator-(float scalar, const Function& f) {
    return [f, scalar](float x) { return scalar - f(x); };
}

Function operator*(float scalar, const Function& f) {
    return f * scalar;
}

Function operator/(float scalar, const Function& f) {
    return [f, scalar](float x) { return scalar / f(x); };
}
} // namespace E::M
