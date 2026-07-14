#pragma once
#include <iosfwd>

#include "Utilities/Math/Vector/Vector2.hpp"

struct Matrix2 {
   float m[2][2];

   Matrix2() = default;

   Matrix2(float mAll);

   Matrix2(float m00, float m01, float m10, float m11);

   Matrix2 Scale(const Vector2 &scale) const;

   Matrix2 Rotate(float radian) const;

   Matrix2 Inverse() const;

   float Determinant() const;

   Matrix2 Transpose() const;

   bool NearlyEquals(const Matrix2 &mat2, float epsilon = Math::EPSILONF) const;

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
