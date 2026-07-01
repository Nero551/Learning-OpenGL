#include "Vector.h"
#include <cmath>
#include <iostream>
#include <ostream>

Vector2::Vector2(float x, float y) : x(x), y(y) {}

//?Operators

//* Vectors
Vector2 Vector2::operator+(const Vector2 &vec2) const { return {x + vec2.x, y + vec2.y}; }
Vector2 Vector2::operator-(const Vector2 &vec2) const { return {x - vec2.x, y - vec2.y}; }

Vector2 &Vector2::operator+=(const Vector2 &vec2) { return *this = *this + vec2; }
Vector2 &Vector2::operator-=(const Vector2 &vec2) { return *this = *this - vec2; }

//* Scalars
Vector2 Vector2::operator+(float scalar) const { return {x + scalar, y + scalar}; }
Vector2 Vector2::operator-(float scalar) const { return {x - scalar, y - scalar}; }
Vector2 Vector2::operator*(float scalar) const { return {x * scalar, y * scalar}; }
Vector2 Vector2::operator/(float scalar) const { return {x / scalar, y / scalar}; }

Vector2 &Vector2::operator+=(float scalar) { return *this = *this + scalar; }
Vector2 &Vector2::operator-=(float scalar) { return *this = *this - scalar; }
Vector2 &Vector2::operator*=(float scalar) { return *this = *this * scalar; }
Vector2 &Vector2::operator/=(float scalar) { return *this = *this / scalar; }

Vector2 operator+(float scalar, const Vector2 &vec2) { return vec2 + scalar; }
Vector2 operator-(float scalar, const Vector2 &vec2) { return {scalar - vec2.x, scalar - vec2.y}; }
Vector2 operator*(float scalar, const Vector2 &vec2) { return vec2 * scalar; }
Vector2 operator/(float scalar, const Vector2 &vec2) { return {scalar / vec2.x, scalar / vec2.y}; }
Vector2 Vector2::operator-() const { return -1 * *this; }

//* Equality
bool Vector2::operator==(const Vector2 &vec2) const { return x == vec2.x && y == vec2.y; }
bool Vector2::operator!=(const Vector2 &vec2) const { return !(*this == vec2); }

//* Others
std::ostream &operator<<(std::ostream &os, const Vector2 &vec2) {
  os << "(" << vec2.x << ", " << vec2.y << ")";
  return os;
}

//?Methods
float Vector2::LengthSquared() const { return x * x + y * y; }

float Vector2::Length() const { return std::sqrt(LengthSquared()); }

float Vector2::Dot(const Vector2 &vec2) const { return x * vec2.x + y * vec2.y; }

float Vector2::Distance(const Vector2 &vec2) const { return (*this - vec2).Length(); }

Vector2 Vector2::Normalized() const {
  float length = Length();
  if (length == 0) {
    return Zero;
  }
  return {x / length, y / length};
}

//?Statics
Vector2 const Vector2::Zero = Vector2(0, 0);