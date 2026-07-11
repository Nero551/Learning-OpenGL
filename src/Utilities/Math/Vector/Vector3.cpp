#include "Vector3.hpp"

#include "Utilities/Math/MathUtils.hpp"

#include <cmath>
#include <ostream>

Vector3::Vector3(float x, float y, float z) : x(x), y(y), z(z) {
}

//?Operators

//*Vectors
Vector3 Vector3::operator+(const Vector3 &vec3) const { return {x + vec3.x, y + vec3.y, z + vec3.z}; }
Vector3 Vector3::operator-(const Vector3 &vec3) const { return {x - vec3.x, y - vec3.y, z - vec3.z}; }

Vector3 &Vector3::operator+=(const Vector3 &vec3) { return *this = *this + vec3; }
Vector3 &Vector3::operator-=(const Vector3 &vec3) { return *this = *this - vec3; }

//*Scalars
Vector3 Vector3::operator+(float scalar) const { return {x + scalar, y + scalar, z + scalar}; }
Vector3 Vector3::operator-(float scalar) const { return {x - scalar, y - scalar, z - scalar}; }
Vector3 Vector3::operator*(float scalar) const { return {x * scalar, y * scalar, z * scalar}; }
Vector3 Vector3::operator/(float scalar) const { return {x / scalar, y / scalar, z / scalar}; }

Vector3 &Vector3::operator+=(float scalar) { return *this = *this + scalar; }
Vector3 &Vector3::operator-=(float scalar) { return *this = *this - scalar; }
Vector3 &Vector3::operator*=(float scalar) { return *this = *this * scalar; }
Vector3 &Vector3::operator/=(float scalar) { return *this = *this / scalar; }

Vector3 operator+(float scalar, const Vector3 &vec3) { return vec3 + scalar; }
Vector3 operator-(float scalar, const Vector3 &vec3) { return {scalar - vec3.x, scalar - vec3.y, scalar - vec3.z}; }
Vector3 operator*(float scalar, const Vector3 &vec3) { return vec3 * scalar; }
Vector3 operator/(float scalar, const Vector3 &vec3) { return {scalar / vec3.x, scalar / vec3.y, scalar / vec3.z}; }
Vector3 Vector3::operator-() const { return -1 * *this; }

//*Equality
bool Vector3::operator==(const Vector3 &vec3) const { return x == vec3.x && y == vec3.y && z == vec3.z; }
bool Vector3::operator!=(const Vector3 &vec3) const { return !(*this == vec3); }

//* Others
std::ostream &operator<<(std::ostream &os, const Vector3 &vec3) {
   os << "(" << vec3.x << ", " << vec3.y << ", " << vec3.z << ")";
   return os;
}

//?Methods
float Vector3::LengthSquared() const { return x * x + y * y + z * z; }

float Vector3::Length() const { return std::sqrt(LengthSquared()); }

float Vector3::Dot(const Vector3 &vec3) const { return x * vec3.x + y * vec3.y + z * vec3.z; }

Vector3 Vector3::Cross(const Vector3 &vec3) const {
   return {y * vec3.z - z * vec3.y, z * vec3.x - x * vec3.z, x * vec3.y - y * vec3.x};
}

float Vector3::Distance(const Vector3 &vec3) const { return (*this - vec3).Length(); }

Vector3 Vector3::Normalized() const {
   float length = Length();
   if (length == 0) {
      return Zero;
   }
   return {x / length, y / length, z / length};
}

bool Vector3::IsParallelTo(const Vector3 &vec3) const {
   if (*this == Vector3::Zero || vec3 == Vector3::Zero) {
      return false;
   }

   return Cross(vec3).LengthSquared() < Math::EPSILONF;
}

bool Vector3::IsPerpendicularTo(const Vector3 &vec3) const {
   if (*this == Vector3::Zero || vec3 == Vector3::Zero) {
      return false;
   }

   return std::abs(Dot(vec3)) < Math::EPSILONF;
}

//?Statics
Vector3 const Vector3::Zero = Vector3(0, 0, 0);
Vector3 const Vector3::Up = Vector3(0, 1, 0);
Vector3 const Vector3::One = Vector3(1, 1, 1);
Vector3 const Vector3::Right = Vector3(1, 0, 0);
Vector3 const Vector3::Forward = Vector3(0, 0, 1);
