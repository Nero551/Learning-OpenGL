#pragma once

#include "Vector.h"
#include <ostream>
struct Matrix2 {
  float m[2][2];

  Matrix2();
  Matrix2(float mAll);
  Matrix2(float m00, float m01, float m10, float m11);

  Matrix2 Scale(const Vector2 &scale) const;
  Matrix2 Rotate(float radian) const;

  Matrix2 operator+(const Matrix2 &mat2) const;
  Matrix2 operator-(const Matrix2 &mat2) const;
  Matrix2 operator*(const Matrix2 &mat2) const;

  Matrix2 &operator+=(const Matrix2 &mat2);
  Matrix2 &operator-=(const Matrix2 &mat2);
  Matrix2 &operator*=(const Matrix2 &mat2);

  Vector2 operator*(const Vector2 &vec2) const;

  Matrix2 operator*(float scalar) const;
  Matrix2 operator/(float scalar) const;

  Matrix2 &operator*=(float scalar);
  Matrix2 &operator/=(float scalar);

  Matrix2 operator-() const;
  bool operator==(const Matrix2 &mat2) const;
  bool operator!=(const Matrix2 &mat2) const;

  static const Matrix2 Zero;
  static const Matrix2 Identity;
};

Matrix2 operator*(float scalar, const Matrix2 &mat2);
std::ostream &operator<<(std::ostream &os, const Matrix2 &mat2);

struct Matrix3 {
  float m[3][3];

  Matrix3();
  Matrix3(float mAll);
  Matrix3(float m00, float m01, float m02, float m10, float m11, float m12, float m20, float m21, float m22);

  Matrix3 Scale(const Vector3 &scale) const;
  Matrix3 RotateX(float radian) const;
  Matrix3 RotateY(float radian) const;
  Matrix3 RotateZ(float radian) const;

  Matrix3 operator+(const Matrix3 &mat3) const;
  Matrix3 operator-(const Matrix3 &mat3) const;
  Matrix3 operator*(const Matrix3 &mat3) const;

  Matrix3 &operator+=(const Matrix3 &mat3);
  Matrix3 &operator-=(const Matrix3 &mat3);
  Matrix3 &operator*=(const Matrix3 &mat3);

  Vector3 operator*(const Vector3 &vec3) const;

  Matrix3 operator*(float scalar) const;
  Matrix3 operator/(float scalar) const;

  Matrix3 &operator*=(float scalar);
  Matrix3 &operator/=(float scalar);

  Matrix3 operator-() const;

  bool operator==(const Matrix3 &mat3) const;
  bool operator!=(const Matrix3 &mat3) const;

  static const Matrix3 Zero;
  static const Matrix3 Identity;
};

Matrix3 operator*(float scalar, const Matrix3 &mat3);
std::ostream &operator<<(std::ostream &os, const Matrix3 &mat3);

struct Matrix4 {
  float m[4][4];

  Matrix4();
  Matrix4(float mAll);
  Matrix4(float m00, float m01, float m02, float m03, float m10, float m11, float m12, float m13, float m20, float m21,
    float m22, float m23, float m30, float m31, float m32, float m33);

  Matrix4 Translate(const Vector3 &translation) const;
  Matrix4 Scale(const Vector3 &scale) const;
  Matrix4 RotateX(float radian) const;
  Matrix4 RotateY(float radian) const;
  Matrix4 RotateZ(float radian) const;

  Matrix4 operator+(const Matrix4 &mat4) const;
  Matrix4 operator-(const Matrix4 &mat4) const;
  Matrix4 operator*(const Matrix4 &mat4) const;

  Matrix4 &operator+=(const Matrix4 &mat4);
  Matrix4 &operator-=(const Matrix4 &mat4);
  Matrix4 &operator*=(const Matrix4 &mat4);

  Vector4 operator*(const Vector4 &vec4) const;

  Matrix4 operator*(float scalar) const;
  Matrix4 operator/(float scalar) const;

  Matrix4 &operator*=(float scalar);
  Matrix4 &operator/=(float scalar);

  Matrix4 operator-() const;

  bool operator==(const Matrix4 &mat4) const;
  bool operator!=(const Matrix4 &mat4) const;

  static Matrix4 Orthographic(float left, float right, float top, float bottom, float near, float far);
  static Matrix4 Perspective(float fovRad, float aspectRatio, float near, float far);

  static const Matrix4 Zero;
  static const Matrix4 Identity;
};

Matrix4 operator*(float scalar, const Matrix4 &mat4);
std::ostream &operator<<(std::ostream &os, const Matrix4 &mat4);