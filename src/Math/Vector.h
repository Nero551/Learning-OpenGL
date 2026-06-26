#pragma once

#include <ostream>
struct Vector2 {
  float x;
  float y;
  Vector2(float x, float y);
  float LengthSquared() const;
  float Length() const;
  Vector2 Normalized() const;
  float Dot(const Vector2 &vec2) const;
  float Distance(const Vector2 &vec2) const;
  Vector2 operator+(const Vector2 &vec2) const;
  Vector2 operator-(const Vector2 &vec2) const;
  Vector2 operator*(float scalar) const;
  Vector2 operator/(float scalar) const;
  Vector2 &operator+=(const Vector2 &vec2);
  Vector2 &operator-=(const Vector2 &vec2);
  Vector2 &operator*=(float scalar);
  Vector2 &operator/=(float scalar);
};
Vector2 operator*(float scalar, const Vector2 &vec2);
Vector2 operator/(float scalar, const Vector2 &vec2);
std::ostream &operator<<(std::ostream &os, const Vector2 &vec);

struct Vector3 {
  float x;
  float y;
  float z;
  Vector3(float x, float y, float z);
  float LengthSquared() const;
  float Length() const;
  Vector3 Normalized() const;
  float Dot(const Vector3 &vec3) const;
  float Distance(const Vector3 &vec3) const;
  Vector3 operator+(const Vector3 &vec3) const;
  Vector3 operator-(const Vector3 &vec3) const;
  Vector3 operator*(float scalar) const;
  Vector3 operator/(float scalar) const;
  Vector3 &operator+=(const Vector3 &vec3);
  Vector3 &operator-=(const Vector3 &vec3);
  Vector3 &operator*=(float scalar);
  Vector3 &operator/=(float scalar);

  static const Vector3 Zero;
  static const Vector3 One;
  static const Vector3 Up;
  static const Vector3 Forward;
};
Vector3 operator*(float scalar, const Vector3 &vec3);
Vector3 operator/(float scalar, const Vector3 &vec3);
std::ostream &operator<<(std::ostream &os, const Vector3 &vec);

struct Vector4 {
  float x;
  float y;
  float z;
  float w;
  Vector4(float x, float y, float z, float w);
  float LengthSquared() const;
  float Length() const;
  Vector4 Normalized() const;
  float Dot(const Vector4 &vec4) const;
  float Distance(const Vector4 &vec4) const;
  Vector4 operator+(const Vector4 &vec4) const;
  Vector4 operator-(const Vector4 &vec4) const;
  Vector4 operator*(float scalar) const;
  Vector4 operator/(float scalar) const;
  Vector4 &operator+=(const Vector4 &vec4);
  Vector4 &operator-=(const Vector4 &vec4);
  Vector4 &operator*=(float scalar);
  Vector4 &operator/=(float scalar);
};
Vector4 operator*(float scalar, const Vector4 &vec4);
Vector4 operator/(float scalar, const Vector4 &vec4);
std::ostream &operator<<(std::ostream &os, const Vector4 &vec);
