module;

#include <cmath>
#include <ostream>

export module Matrix2;

import LoggerService;
import MathUtils;
import Vector2;

export struct Matrix2 {
  float m[2][2];

  Matrix2() = default;

  Matrix2(float mAll) {
    for (int row = 0; row < 2; row++)
      for (int col = 0; col < 2; col++)
        m[row][col] = mAll;
  }

  Matrix2(float m00, float m01, float m10, float m11) {
    m[0][0] = m00;
    m[0][1] = m01;
    m[1][0] = m10;
    m[1][1] = m11;
  }

  // Methods

  Matrix2 Scale(const Vector2 &scale) const {
    Matrix2 scaleMatrix = Identity;
    scaleMatrix.m[0][0] = scale.x;
    scaleMatrix.m[1][1] = scale.y;
    return *this * scaleMatrix;
  }

  Matrix2 Rotate(float radian) const {
    Matrix2 rotationMatrix = Identity;
    rotationMatrix.m[0][0] = std::cos(radian);
    rotationMatrix.m[0][1] = -std::sin(radian);
    rotationMatrix.m[1][0] = std::sin(radian);
    rotationMatrix.m[1][1] = std::cos(radian);
    return *this * rotationMatrix;
  }

  Matrix2 Transpose() const {
    Matrix2 result;

    for (int row = 0; row < 2; row++)
      for (int col = 0; col < 2; col++)
        result.m[row][col] = m[col][row];

    return result;
  }

  float Determinant() const { return m[0][0] * m[1][1] - m[0][1] * m[1][0]; }

  Matrix2 Inverse() const {
    float det = Determinant();

    if (std::abs(det) < Math::EPSILONF) {
      LoggerService::Error("Matrix is not invertible");
      return Identity;
    }

    return Matrix2(m[1][1], -m[0][1], -m[1][0], m[0][0]) / det;
  }

  // Matrix operators

  Matrix2 operator+(const Matrix2 &rhs) const {
    return {m[0][0] + rhs.m[0][0], m[0][1] + rhs.m[0][1], m[1][0] + rhs.m[1][0], m[1][1] + rhs.m[1][1]};
  }

  Matrix2 operator-(const Matrix2 &rhs) const {
    return {m[0][0] - rhs.m[0][0], m[0][1] - rhs.m[0][1], m[1][0] - rhs.m[1][0], m[1][1] - rhs.m[1][1]};
  }

  Matrix2 operator*(const Matrix2 &rhs) const {
    Matrix2 result(0);

    for (int row = 0; row < 2; row++)
      for (int col = 0; col < 2; col++)
        for (int k = 0; k < 2; k++)
          result.m[row][col] += m[row][k] * rhs.m[k][col];

    return result;
  }

  Matrix2 &operator+=(const Matrix2 &rhs) { return *this = *this + rhs; }

  Matrix2 &operator-=(const Matrix2 &rhs) { return *this = *this - rhs; }

  Matrix2 &operator*=(const Matrix2 &rhs) { return *this = *this * rhs; }

  // Vector

  Vector2 operator*(const Vector2 &vec) const {
    return {m[0][0] * vec.x + m[0][1] * vec.y, m[1][0] * vec.x + m[1][1] * vec.y};
  }

  // Scalar

  Matrix2 operator*(float scalar) const {
    return {m[0][0] * scalar, m[0][1] * scalar, m[1][0] * scalar, m[1][1] * scalar};
  }

  Matrix2 operator/(float scalar) const {
    return {m[0][0] / scalar, m[0][1] / scalar, m[1][0] / scalar, m[1][1] / scalar};
  }

  Matrix2 &operator*=(float scalar) { return *this = *this * scalar; }

  Matrix2 &operator/=(float scalar) { return *this = *this / scalar; }

  Matrix2 operator-() const { return *this * -1.0f; }

  // Equality

  bool operator==(const Matrix2 &rhs) const {
    for (int row = 0; row < 2; row++)
      for (int col = 0; col < 2; col++)
        if (m[row][col] != rhs.m[row][col])
          return false;

    return true;
  }

  bool operator!=(const Matrix2 &rhs) const { return !(*this == rhs); }

  static const Matrix2 Zero;
  static const Matrix2 Identity;
};

export inline Matrix2 operator*(float scalar, const Matrix2 &mat) { return mat * scalar; }

export inline std::ostream &operator<<(std::ostream &os, const Matrix2 &mat) {
  os << "[ " << mat.m[0][0] << "  " << mat.m[0][1] << " ]\n";
  os << "[ " << mat.m[1][0] << "  " << mat.m[1][1] << " ]";
  return os;
}

const Matrix2 Matrix2::Zero(0);
const Matrix2 Matrix2::Identity(1, 0, 0, 1);