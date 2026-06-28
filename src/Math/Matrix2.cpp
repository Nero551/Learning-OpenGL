#include "Matrix.h"
#include "Vector.h"

Matrix2::Matrix2(float m00, float m01, float m10, float m11) {
  m[0][0] = m00;
  m[0][1] = m01;
  m[1][0] = m10;
  m[1][1] = m11;
}

//? Operations

//* Matrices
Matrix2 Matrix2::operator+(const Matrix2 &mat2) const {
  return {m[0][0] + mat2.m[0][0], m[0][1] + mat2.m[0][1], m[1][0] + mat2.m[1][0], m[1][1] + mat2.m[1][1]};
}
Matrix2 Matrix2::operator-(const Matrix2 &mat2) const {
  return {m[0][0] - mat2.m[0][0], m[0][1] - mat2.m[0][1], m[1][0] - mat2.m[1][0], m[1][1] - mat2.m[1][1]};
}

Matrix2 Matrix2::operator*(const Matrix2 &mat2) const {
  Matrix2 result = Matrix2::Zero;

  for (int row = 0; row < 2; row++) {
    for (int col = 0; col < 2; col++) {
      result.m[row][col] = 0;

      for (int k = 0; k < 2; k++) {
        result.m[row][col] += m[row][k] * mat2.m[k][col];
      }
    }
  }

  return result;
}

Matrix2 &Matrix2::operator+=(const Matrix2 &mat2) { return *this = *this + mat2; }
Matrix2 &Matrix2::operator-=(const Matrix2 &mat2) { return *this = *this - mat2; }
Matrix2 &Matrix2::operator*=(const Matrix2 &mat2) { return *this = *this * mat2; }

//* Vectors
Vector2 Matrix2::operator*(const Vector2 &vec2) const {
  return {m[0][0] * vec2.x + m[0][1] * vec2.y, m[1][0] * vec2.x + m[1][1] * vec2.y};
}

//* Scalars
Matrix2 Matrix2::operator*(float scalar) const {
  return {scalar * m[0][0], scalar * m[0][1], scalar * m[1][0], scalar * m[1][1]};
}

Matrix2 Matrix2::operator/(float scalar) const {
  return {m[0][0] / scalar, m[0][1] / scalar, m[1][0] / scalar, m[1][1] / scalar};
}

Matrix2 &Matrix2::operator*=(float scalar) { return *this = *this * scalar; }
Matrix2 &Matrix2::operator/=(float scalar) { return *this = *this / scalar; }

Matrix2 Matrix2::operator-() const { return *this * -1; }

//? Methods

//? Statics
Matrix2 const Matrix2::Zero = Matrix2(0, 0, 0, 0);
Matrix2 const Matrix2::Identity = Matrix2(1, 0, 0, 1);