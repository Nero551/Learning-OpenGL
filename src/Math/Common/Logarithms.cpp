#include "Logarithms.hpp"

namespace E::M {
float Ln(float x) {
    return std::log(x);
}

float Log(float base, float x) {
    return Ln(x) / Ln(base);
}
} // namespace E::M
