#pragma once
#include <iosfwd>

struct Vector4 {
   float x;
   float y;
   float z;
   float w;

   Vector4() = default;

   Vector4(float x, float y, float z, float w);

   float LengthSquared() const;

   float Length() const;

   Vector4 Normalized() const;

   float Dot(const Vector4 &vec4) const;

   float Distance(const Vector4 &vec4) const;

   Vector4 operator+(const Vector4 &vec4) const;

   Vector4 operator-(const Vector4 &vec4) const;

   Vector4 operator*(const Vector4 &vec4) const;

   Vector4 &operator+=(const Vector4 &vec4);

   Vector4 &operator-=(const Vector4 &vec4);

   Vector4 &operator*=(const Vector4 &vec4);

   Vector4 operator+(float scalar) const;

   Vector4 operator-(float scalar) const;

   Vector4 operator*(float scalar) const;

   Vector4 operator/(float scalar) const;

   Vector4 &operator+=(float scalar);

   Vector4 &operator-=(float scalar);

   Vector4 &operator*=(float scalar);

   Vector4 &operator/=(float scalar);

   Vector4 operator-() const;

   bool operator==(const Vector4 &vec4) const;

   bool operator!=(const Vector4 &vec4) const;

   static const Vector4 Zero;
};

Vector4 operator+(float scalar, const Vector4 &vec4);

Vector4 operator-(float scalar, const Vector4 &vec4);

Vector4 operator*(float scalar, const Vector4 &vec4);

Vector4 operator/(float scalar, const Vector4 &vec4);

std::ostream &operator<<(std::ostream &os, const Vector4 &vec4);
