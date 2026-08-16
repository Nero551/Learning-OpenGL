#include "Quaternion.hpp"

namespace E::M {
Quaternion::Quaternion() : w(0), x(0), y(0), z(0) {}

Quaternion::Quaternion(const float all) : w(all), x(all), y(all), z(all) {}

Quaternion::Quaternion(const float w, const float x, const float y, const float z) : w(w), x(x), y(y), z(z) {}

std::ostream& operator<<(std::ostream& os, const Quaternion& q) {
    os << "(" << q.x << ", " << q.y << ", " << q.z << ", " << q.w << ")";
    return os;
}
} // namespace E::M
