#pragma once
#include "Matrix3.hpp"
#include "Utilities/Math/Vector/Vector4.hpp"

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
  float Determinant() const;
  Matrix4 Transpose() const;
  Matrix4 Inverse() const;
  Matrix3 Minor(int row, int col) const;

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

  static Matrix4 Orthographic(float left, float right, float bottom, float top, float near, float far);
  static Matrix4 Perspective(float fovRad, float aspectRatio, float near, float far);
  static Matrix4 LookAt(const Vector3 pos, const Vector3 target, const Vector3 up);

  static const Matrix4 Zero;
  static const Matrix4 Identity;
};

Matrix4 operator*(float scalar, const Matrix4 &mat4);
std::ostream &operator<<(std::ostream &os, const Matrix4 &mat4);