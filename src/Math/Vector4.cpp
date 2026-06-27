#include "Vector.h"
#include <cmath>
#include <iostream>
#include <ostream>

Vector4::Vector4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

//?Operators

//*Vectors
Vector4 Vector4::operator+(const Vector4 &vec4) const { return {x + vec4.x, y + vec4.y, z + vec4.z, w + vec4.w}; }
Vector4 Vector4::operator-(const Vector4 &vec4) const { return {x - vec4.x, y - vec4.y, z - vec4.z, w - vec4.w}; }

Vector4 &Vector4::operator+=(const Vector4 &vec4) { return *this = *this + vec4; }
Vector4 &Vector4::operator-=(const Vector4 &vec4) { return *this = *this - vec4; }

//*Scalars
Vector4 Vector4::operator+(float scalar) const { return {x + scalar, y + scalar, z + scalar, w + scalar}; }
Vector4 Vector4::operator-(float scalar) const { return {x - scalar, y - scalar, z - scalar, w - scalar}; }
Vector4 Vector4::operator*(float scalar) const { return {x * scalar, y * scalar, z * scalar, w * scalar}; }
Vector4 Vector4::operator/(float scalar) const { return {x / scalar, y / scalar, z / scalar, w / scalar}; }

Vector4 &Vector4::operator+=(float scalar) { return *this = *this + scalar; }
Vector4 &Vector4::operator-=(float scalar) { return *this = *this - scalar; }
Vector4 &Vector4::operator*=(float scalar) { return *this = *this * scalar; }
Vector4 &Vector4::operator/=(float scalar) { return *this = *this / scalar; }

Vector4 operator+(float scalar, const Vector4 &vec4) { return vec4 + scalar; }
Vector4 operator-(float scalar, const Vector4 &vec4) { return {scalar - vec4.x, scalar - vec4.y, scalar - vec4.z, scalar - vec4.w}; }
Vector4 operator*(float scalar, const Vector4 &vec4) { return vec4 * scalar; }
Vector4 operator/(float scalar, const Vector4 &vec4) { return {scalar / vec4.x, scalar / vec4.y, scalar / vec4.z, scalar / vec4.w}; }
Vector4 Vector4::operator-() const { return -1 * *this; }

//*Equality
bool Vector4::operator==(const Vector4 &vec4) const { return x == vec4.x && y == vec4.y && z == vec4.z && w == vec4.w; }
bool Vector4::operator!=(const Vector4 &vec4) const { return !(*this == vec4); }

//* Others
std::ostream &operator<<(std::ostream &os, const Vector4 &vec4) {
  os << "(" << vec4.x << ", " << vec4.y << ", " << vec4.z << ", " << vec4.w << ")";
  return os;
}

//?Methods
float Vector4::LengthSquared() const { return x * x + y * y + z * z + w * w; }
float Vector4::Length() const { return std::sqrt(LengthSquared()); }
float Vector4::Dot(const Vector4 &vec4) const { return x * vec4.x + y * vec4.y + z * vec4.z + w * vec4.w; }
float Vector4::Distance(const Vector4 &vec4) const { return (*this - vec4).Length(); }

Vector4 Vector4::Normalized() const {
  float length = Length();
  if (length == 0) {
    return Zero;
  }
  return {x / length, y / length, z / length, w / length};
}

//?Statics
Vector4 const Vector4::Zero = Vector4(0, 0, 0, 0);