
#include "Matrix3.hpp"

#include "Utilities/Math/MathUtils.hpp"

#include <cmath>
#include "Utilities/Services/LoggerService.hpp"

Matrix3::Matrix3() {}

Matrix3::Matrix3(float mAll) {
  for (int row = 0; row < 3; row++) {
    for (int col = 0; col < 3; col++) {
      m[row][col] = mAll;
    }
  }
}

Matrix3::Matrix3(float m00, float m01, float m02, float m10, float m11, float m12, float m20, float m21, float m22) {
  m[0][0] = m00;
  m[0][1] = m01;
  m[0][2] = m02;

  m[1][0] = m10;
  m[1][1] = m11;
  m[1][2] = m12;

  m[2][0] = m20;
  m[2][1] = m21;
  m[2][2] = m22;
}

//? Operations

//* Matrices
Matrix3 Matrix3::operator+(const Matrix3 &mat3) const {
  return {m[0][0] + mat3.m[0][0], m[0][1] + mat3.m[0][1], m[0][2] + mat3.m[0][2], m[1][0] + mat3.m[1][0],
    m[1][1] + mat3.m[1][1], m[1][2] + mat3.m[1][2], m[2][0] + mat3.m[2][0], m[2][1] + mat3.m[2][1],
    m[2][2] + mat3.m[2][2]};
}

Matrix3 Matrix3::operator-(const Matrix3 &mat3) const {
  return {m[0][0] - mat3.m[0][0], m[0][1] - mat3.m[0][1], m[0][2] - mat3.m[0][2], m[1][0] - mat3.m[1][0],
    m[1][1] - mat3.m[1][1], m[1][2] - mat3.m[1][2], m[2][0] - mat3.m[2][0], m[2][1] - mat3.m[2][1],
    m[2][2] - mat3.m[2][2]};
}

Matrix3 Matrix3::operator*(const Matrix3 &mat3) const {
  Matrix3 result(0);

  for (int row = 0; row < 3; row++) {
    for (int col = 0; col < 3; col++) {
      for (int k = 0; k < 3; k++) {
        result.m[row][col] += m[row][k] * mat3.m[k][col];
      }
    }
  }

  return result;
}

Matrix3 &Matrix3::operator+=(const Matrix3 &mat3) { return *this = *this + mat3; }
Matrix3 &Matrix3::operator-=(const Matrix3 &mat3) { return *this = *this - mat3; }
Matrix3 &Matrix3::operator*=(const Matrix3 &mat3) { return *this = *this * mat3; }

//* Vectors
Vector3 Matrix3::operator*(const Vector3 &vec3) const {
  return {m[0][0] * vec3.x + m[0][1] * vec3.y + m[0][2] * vec3.z,
    m[1][0] * vec3.x + m[1][1] * vec3.y + m[1][2] * vec3.z, m[2][0] * vec3.x + m[2][1] * vec3.y + m[2][2] * vec3.z};
}

//* Scalars
Matrix3 Matrix3::operator*(float scalar) const {
  return {scalar * m[0][0], scalar * m[0][1], scalar * m[0][2], scalar * m[1][0], scalar * m[1][1], scalar * m[1][2],
    scalar * m[2][0], scalar * m[2][1], scalar * m[2][2]};
}

Matrix3 Matrix3::operator/(float scalar) const {
  return {m[0][0] / scalar, m[0][1] / scalar, m[0][2] / scalar, m[1][0] / scalar, m[1][1] / scalar, m[1][2] / scalar,
    m[2][0] / scalar, m[2][1] / scalar, m[2][2] / scalar};
}

Matrix3 &Matrix3::operator*=(float scalar) { return *this = *this * scalar; }
Matrix3 &Matrix3::operator/=(float scalar) { return *this = *this / scalar; }

Matrix3 Matrix3::operator-() const { return *this * -1; }

//* Equality
bool Matrix3::operator==(const Matrix3 &mat3) const {
  for (int row = 0; row < 3; row++) {
    for (int col = 0; col < 3; col++) {
      if (m[row][col] != mat3.m[row][col])
        return false;
    }
  }
  return true;
}

bool Matrix3::operator!=(const Matrix3 &mat3) const { return !(*this == mat3); }

//* Others
Matrix3 operator*(float scalar, const Matrix3 &mat3) { return mat3 * scalar; }

std::ostream &operator<<(std::ostream &os, const Matrix3 &mat3) {
  os << "[ " << mat3.m[0][0] << "  " << mat3.m[0][1] << "  " << mat3.m[0][2] << " ]\n";
  os << "[ " << mat3.m[1][0] << "  " << mat3.m[1][1] << "  " << mat3.m[1][2] << " ]\n";
  os << "[ " << mat3.m[2][0] << "  " << mat3.m[2][1] << "  " << mat3.m[2][2] << " ]";
  return os;
}

//? Methods
Matrix3 Matrix3::Scale(const Vector3 &scale) const {
  Matrix3 scaleMatrix = Matrix3::Identity;
  scaleMatrix.m[0][0] = scale.x;
  scaleMatrix.m[1][1] = scale.y;
  scaleMatrix.m[2][2] = scale.z;

  return *this * scaleMatrix;
}

Matrix3 Matrix3::Translate(const Vector2 &trans) const {
  Matrix3 transMatrix = Matrix3::Identity;

  transMatrix.m[0][2] = trans.x;
  transMatrix.m[1][2] = trans.y;

  return *this * transMatrix;
}

Matrix3 Matrix3::RotateX(float radian) const {
  Matrix3 rotationMatrix = Matrix3::Identity;
  rotationMatrix.m[1][1] = std::cos(radian);
  rotationMatrix.m[2][1] = std::sin(radian);
  rotationMatrix.m[1][2] = -std::sin(radian);
  rotationMatrix.m[2][2] = std::cos(radian);

  return *this * rotationMatrix;
}

Matrix3 Matrix3::RotateY(float radian) const {
  Matrix3 rotationMatrix = Matrix3::Identity;
  rotationMatrix.m[0][0] = std::cos(radian);
  rotationMatrix.m[0][2] = std::sin(radian);
  rotationMatrix.m[2][0] = -std::sin(radian);
  rotationMatrix.m[2][2] = std::cos(radian);

  return *this * rotationMatrix;
}

Matrix3 Matrix3::RotateZ(float radian) const {
  Matrix3 rotationMatrix = Matrix3::Identity;
  rotationMatrix.m[0][0] = std::cos(radian);
  rotationMatrix.m[1][0] = std::sin(radian);
  rotationMatrix.m[0][1] = -std::sin(radian);
  rotationMatrix.m[1][1] = std::cos(radian);

  return *this * rotationMatrix;
}

float Matrix3::Determinant() const {
  return (
    m[0][0] * Minor(0, 0).Determinant() - m[0][1] * Minor(0, 1).Determinant() + m[0][2] * Minor(0, 2).Determinant());
}

Matrix3 Matrix3::Transpose() const {
  Matrix3 result;

  for (int row = 0; row < 3; row++) {
    for (int col = 0; col < 3; col++) {
      result.m[row][col] = m[col][row];
    }
  }

  return result;
}

Matrix3 Matrix3::Inverse() const {
  Matrix3 cofactorMatrix;

  for (int row = 0; row < 3; row++) {
    for (int col = 0; col < 3; col++) {
      Matrix2 minor = Minor(row, col);

      float det = minor.Determinant();

      if ((row + col) % 2 == 1) {
        det = -det;
      }

      cofactorMatrix.m[row][col] = det;
    }
  }

  float det = Determinant();

  if (std::abs(det) < Math::EPSILONF) {
    LoggerService::Error("Matrix is not invertible");
    return Matrix3::Identity;
  }

  return cofactorMatrix.Transpose() / det;
}

Matrix2 Matrix3::Minor(int row, int col) const {
  Matrix2 minor;
  int minorRow = 0;

  for (int r = 0; r < 3; r++) {
    if (r != row) {
      int minorCol = 0;

      for (int c = 0; c < 3; c++) {
        if (c != col) {
          minor.m[minorRow][minorCol] = m[r][c];
          minorCol++;
        }
      }
      minorRow++;
    }
  }

  return minor;
}

//? Statics
Matrix3 const Matrix3::Zero = Matrix3(0);
Matrix3 const Matrix3::Identity = Matrix3(1, 0, 0, 0, 1, 0, 0, 0, 1);