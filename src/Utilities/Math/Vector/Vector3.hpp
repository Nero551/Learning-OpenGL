#pragma once
#include <iosfwd>

struct Vector3 {
   float x;
   float y;
   float z;

   Vector3() = default;

   Vector3(float x, float y, float z);

   float LengthSquared() const;

   float Length() const;

   Vector3 Normalized() const;

   float Dot(const Vector3 &vec3) const;

   Vector3 Cross(const Vector3 &vec3) const;

   float Distance(const Vector3 &vec3) const;

   bool IsParallelTo(const Vector3 &vec3) const;

   bool IsPerpendicularTo(const Vector3 &vec3) const;

   Vector3 operator+(const Vector3 &vec3) const;

   Vector3 operator-(const Vector3 &vec3) const;

   Vector3 &operator+=(const Vector3 &vec3);

   Vector3 &operator-=(const Vector3 &vec3);

   Vector3 operator+(float scalar) const;

   Vector3 operator-(float scalar) const;

   Vector3 operator*(float scalar) const;

   Vector3 operator/(float scalar) const;

   Vector3 &operator+=(float scalar);

   Vector3 &operator-=(float scalar);

   Vector3 &operator*=(float scalar);

   Vector3 &operator/=(float scalar);

   Vector3 operator-() const;

   bool operator==(const Vector3 &vec3) const;

   bool operator!=(const Vector3 &vec3) const;

   static const Vector3 Zero;
   static const Vector3 One;
   static const Vector3 Up;
   static const Vector3 Right;
   static const Vector3 Forward;
};

Vector3 operator+(float scalar, const Vector3 &vec3);

Vector3 operator-(float scalar, const Vector3 &vec3);

Vector3 operator*(float scalar, const Vector3 &vec3);

Vector3 operator/(float scalar, const Vector3 &vec3);

std::ostream &operator<<(std::ostream &os, const Vector3 &vec3);
