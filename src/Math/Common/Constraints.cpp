#include "Constraints.hpp"

namespace E::M {
float Clamp(float value, float min, float max) {
    return std::clamp(value, min, max);
}
} // namespace E::M
