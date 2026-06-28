#include "Vector.h"
struct Matrix2 {
  float m[2][2];
  Matrix2(float m00, float m01, float m10, float m11);

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

  static const Matrix2 Zero;
  static const Matrix2 Identity;
};

Matrix2 operator*(float scalar, const Matrix2 &mat2);
