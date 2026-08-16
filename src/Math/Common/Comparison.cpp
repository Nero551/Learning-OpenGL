#include "Comparison.hpp"

namespace E::M {
bool NearlyEquals(const float a, const float b, const float epsilon) {
    return std::abs(a - b) <= epsilon;
}
} // namespace E::M
