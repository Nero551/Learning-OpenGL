#pragma once

#include <ostream>

struct Vector2 {
   float x;
   float y;

   Vector2() = default;

   Vector2(float x, float y);

   float LengthSquared() const;

   float Length() const;

   Vector2 Normalized() const;

   float Dot(const Vector2 &vec2) const;

   float Distance(const Vector2 &vec2) const;

   Vector2 operator+(const Vector2 &vec2) const;

   Vector2 operator-(const Vector2 &vec2) const;

   Vector2 &operator+=(const Vector2 &vec2);

   Vector2 &operator-=(const Vector2 &vec2);

   Vector2 operator+(float scalar) const;

   Vector2 operator-(float scalar) const;

   Vector2 operator*(float scalar) const;

   Vector2 operator/(float scalar) const;

   Vector2 &operator+=(float scalar);

   Vector2 &operator-=(float scalar);

   Vector2 &operator*=(float scalar);

   Vector2 &operator/=(float scalar);

   Vector2 operator-() const;

   bool operator==(const Vector2 &vec2) const;

   bool operator!=(const Vector2 &vec2) const;

   static const Vector2 Zero;
};

Vector2 operator+(float scalar, const Vector2 &vec2);

Vector2 operator-(float scalar, const Vector2 &vec2);

Vector2 operator*(float scalar, const Vector2 &vec2);

Vector2 operator/(float scalar, const Vector2 &vec2);

std::ostream &operator<<(std::ostream &os, const Vector2 &vec2);
