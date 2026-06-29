#include "Matrix.h"
#include "Vector.h"
#include <cmath>

Matrix4::Matrix4() {}

Matrix4::Matrix4(float mAll) {
  for (int row = 0; row < 4; row++) {
    for (int col = 0; col < 4; col++) {
      m[row][col] = mAll;
    }
  }
}

Matrix4::Matrix4(float m00, float m01, float m02, float m03, float m10, float m11, float m12, float m13, float m20,
  float m21, float m22, float m23, float m30, float m31, float m32, float m33) {
  m[0][0] = m00;
  m[0][1] = m01;
  m[0][2] = m02;
  m[0][3] = m03;

  m[1][0] = m10;
  m[1][1] = m11;
  m[1][2] = m12;
  m[1][3] = m13;

  m[2][0] = m20;
  m[2][1] = m21;
  m[2][2] = m22;
  m[2][3] = m23;

  m[3][0] = m30;
  m[3][1] = m31;
  m[3][2] = m32;
  m[3][3] = m33;
}

//? Operations

//* Matrices
Matrix4 Matrix4::operator+(const Matrix4 &mat4) const {
  return {m[0][0] + mat4.m[0][0], m[0][1] + mat4.m[0][1], m[0][2] + mat4.m[0][2], m[0][3] + mat4.m[0][3],
    m[1][0] + mat4.m[1][0], m[1][1] + mat4.m[1][1], m[1][2] + mat4.m[1][2], m[1][3] + mat4.m[1][3],
    m[2][0] + mat4.m[2][0], m[2][1] + mat4.m[2][1], m[2][2] + mat4.m[2][2], m[2][3] + mat4.m[2][3],
    m[3][0] + mat4.m[3][0], m[3][1] + mat4.m[3][1], m[3][2] + mat4.m[3][2], m[3][3] + mat4.m[3][3]};
}

Matrix4 Matrix4::operator-(const Matrix4 &mat4) const {
  return {m[0][0] - mat4.m[0][0], m[0][1] - mat4.m[0][1], m[0][2] - mat4.m[0][2], m[0][3] - mat4.m[0][3],
    m[1][0] - mat4.m[1][0], m[1][1] - mat4.m[1][1], m[1][2] - mat4.m[1][2], m[1][3] - mat4.m[1][3],
    m[2][0] - mat4.m[2][0], m[2][1] - mat4.m[2][1], m[2][2] - mat4.m[2][2], m[2][3] - mat4.m[2][3],
    m[3][0] - mat4.m[3][0], m[3][1] - mat4.m[3][1], m[3][2] - mat4.m[3][2], m[3][3] - mat4.m[3][3]};
}

Matrix4 Matrix4::operator*(const Matrix4 &mat4) const {
  Matrix4 result(0);

  for (int row = 0; row < 4; row++) {
    for (int col = 0; col < 4; col++) {
      for (int k = 0; k < 4; k++) {
        result.m[row][col] += m[row][k] * mat4.m[k][col];
      }
    }
  }

  return result;
}

Matrix4 &Matrix4::operator+=(const Matrix4 &mat4) { return *this = *this + mat4; }
Matrix4 &Matrix4::operator-=(const Matrix4 &mat4) { return *this = *this - mat4; }
Matrix4 &Matrix4::operator*=(const Matrix4 &mat4) { return *this = *this * mat4; }

//* Vectors
Vector4 Matrix4::operator*(const Vector4 &vec4) const {
  return {m[0][0] * vec4.x + m[0][1] * vec4.y + m[0][2] * vec4.z + m[0][3] * vec4.w,
    m[1][0] * vec4.x + m[1][1] * vec4.y + m[1][2] * vec4.z + m[1][3] * vec4.w,
    m[2][0] * vec4.x + m[2][1] * vec4.y + m[2][2] * vec4.z + m[2][3] * vec4.w,
    m[3][0] * vec4.x + m[3][1] * vec4.y + m[3][2] * vec4.z + m[3][3] * vec4.w};
}

//* Scalars
Matrix4 Matrix4::operator*(float scalar) const {
  return {scalar * m[0][0], scalar * m[0][1], scalar * m[0][2], scalar * m[0][3], scalar * m[1][0], scalar * m[1][1],
    scalar * m[1][2], scalar * m[1][3], scalar * m[2][0], scalar * m[2][1], scalar * m[2][2], scalar * m[2][3],
    scalar * m[3][0], scalar * m[3][1], scalar * m[3][2], scalar * m[3][3]};
}

Matrix4 Matrix4::operator/(float scalar) const {
  return {m[0][0] / scalar, m[0][1] / scalar, m[0][2] / scalar, m[0][3] / scalar, m[1][0] / scalar, m[1][1] / scalar,
    m[1][2] / scalar, m[1][3] / scalar, m[2][0] / scalar, m[2][1] / scalar, m[2][2] / scalar, m[2][3] / scalar,
    m[3][0] / scalar, m[3][1] / scalar, m[3][2] / scalar, m[3][3] / scalar};
}

Matrix4 &Matrix4::operator*=(float scalar) { return *this = *this * scalar; }
Matrix4 &Matrix4::operator/=(float scalar) { return *this = *this / scalar; }

Matrix4 Matrix4::operator-() const { return *this * -1; }

//* Equality
bool Matrix4::operator==(const Matrix4 &mat4) const {
  for (int row = 0; row < 4; row++) {
    for (int col = 0; col < 4; col++) {
      if (m[row][col] != mat4.m[row][col])
        return false;
    }
  }

  return true;
}

bool Matrix4::operator!=(const Matrix4 &mat4) const { return !(*this == mat4); }

//* Others
Matrix4 operator*(float scalar, const Matrix4 &mat4) { return mat4 * scalar; }

std::ostream &operator<<(std::ostream &os, const Matrix4 &mat) {
  os << "[ " << mat.m[0][0] << "  " << mat.m[0][1] << "  " << mat.m[0][2] << "  " << mat.m[0][3] << " ]\n";
  os << "[ " << mat.m[1][0] << "  " << mat.m[1][1] << "  " << mat.m[1][2] << "  " << mat.m[1][3] << " ]\n";
  os << "[ " << mat.m[2][0] << "  " << mat.m[2][1] << "  " << mat.m[2][2] << "  " << mat.m[2][3] << " ]\n";
  os << "[ " << mat.m[3][0] << "  " << mat.m[3][1] << "  " << mat.m[3][2] << "  " << mat.m[3][3] << " ]";
  return os;
}

//? Methods
Matrix4 Matrix4::Scale(const Vector3 &scale) const {
  Matrix4 scaleMatrix = Matrix4::Identity;
  scaleMatrix.m[0][0] = scale.x;
  scaleMatrix.m[1][1] = scale.y;
  scaleMatrix.m[2][2] = scale.z;

  return *this * scaleMatrix;
}

Matrix4 Matrix4::Translate(const Vector3 &translation) const {
  Matrix4 transMatrix = Matrix4::Identity;
  transMatrix.m[0][3] = translation.x;
  transMatrix.m[1][3] = translation.y;
  transMatrix.m[2][3] = translation.z;

  return *this * transMatrix;
}

Matrix4 Matrix4::RotateX(float radian) const {
  Matrix4 rotationMatrix = Matrix4::Identity;
  rotationMatrix.m[1][1] = std::cos(radian);
  rotationMatrix.m[2][1] = std::sin(radian);
  rotationMatrix.m[1][2] = -std::sin(radian);
  rotationMatrix.m[2][2] = std::cos(radian);

  return *this * rotationMatrix;
}

Matrix4 Matrix4::RotateY(float radian) const {
  Matrix4 rotationMatrix = Matrix4::Identity;
  rotationMatrix.m[0][0] = std::cos(radian);
  rotationMatrix.m[0][2] = std::sin(radian);
  rotationMatrix.m[2][0] = -std::sin(radian);
  rotationMatrix.m[2][2] = std::cos(radian);

  return *this * rotationMatrix;
}

Matrix4 Matrix4::RotateZ(float radian) const {
  Matrix4 rotationMatrix = Matrix4::Identity;
  rotationMatrix.m[0][0] = std::cos(radian);
  rotationMatrix.m[1][0] = std::sin(radian);
  rotationMatrix.m[0][1] = -std::sin(radian);
  rotationMatrix.m[1][1] = std::cos(radian);

  return *this * rotationMatrix;
}

Matrix4 Matrix4::Orthographic(float left, float right, float bottom, float top, float near, float far) {
  Matrix4 m = Matrix4::Identity;

  m.m[0][0] = 2.0f / (right - left);
  m.m[1][1] = 2.0f / (top - bottom);
  m.m[2][2] = -2.0f / (far - near);

  m.m[0][3] = -(right + left) / (right - left);
  m.m[1][3] = -(top + bottom) / (top - bottom);
  m.m[2][3] = -(far + near) / (far - near);

  return m;
}

Matrix4 Matrix4::Perspective(float fov, float aspect, float near, float far) {
  Matrix4 m = Matrix4::Zero;

  float f = 1.0f / std::tan(fov * 0.5f);

  m.m[0][0] = f / aspect;
  m.m[1][1] = f;

  m.m[2][2] = -(far + near) / (far - near);
  m.m[2][3] = -(2.0f * far * near) / (far - near);

  m.m[3][2] = -1.0f;

  return m;
}

//? Statics
Matrix4 const Matrix4::Zero = Matrix4(0);
Matrix4 const Matrix4::Identity = Matrix4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);