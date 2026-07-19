#pragma once
#include "Matrix2.hpp"
#include "Utilities/Math/Vector/Vector3.hpp"

struct Matrix3 {
    float m[3][3] = {};

    Matrix3() = default;

    Matrix3(float mAll);

    Matrix3(float m00, float m01, float m02, float m10, float m11, float m12, float m20, float m21, float m22);

    [[nodiscard]] Matrix3 Scale(const Vector3& scale) const;

    [[nodiscard]] Matrix3 RotateX(float radian) const;

    [[nodiscard]] Matrix3 RotateY(float radian) const;

    [[nodiscard]] Matrix3 RotateZ(float radian) const;

    [[nodiscard]] Matrix3 Rotate(const Vector3& eulerRotation) const;

    [[nodiscard]] Matrix3 RotateAroundAxis(const Vector3& axis, float radian) const;

    [[nodiscard]] Matrix3 Translate(const Vector2& trans) const;

    [[nodiscard]] float Determinant() const;

    [[nodiscard]] Matrix3 Transpose() const;

    [[nodiscard]] Matrix3 Inverse() const;

    [[nodiscard]] Matrix2 Minor(int row, int col) const;

    [[nodiscard]] bool NearlyEquals(const Matrix3& mat3, float epsilon = Math::EPSILONF) const;

    Matrix3 operator+(const Matrix3& mat3) const;

    Matrix3 operator-(const Matrix3& mat3) const;

    Matrix3 operator*(const Matrix3& mat3) const;

    Matrix3& operator+=(const Matrix3& mat3);

    Matrix3& operator-=(const Matrix3& mat3);

    Matrix3& operator*=(const Matrix3& mat3);

    Vector3 operator*(const Vector3& vec3) const;

    Matrix3 operator*(float scalar) const;

    Matrix3 operator/(float scalar) const;

    Matrix3& operator*=(float scalar);

    Matrix3& operator/=(float scalar);

    Matrix3 operator-() const;

    bool operator==(const Matrix3& mat3) const;

    bool operator!=(const Matrix3& mat3) const;

    static const Matrix3 Zero;
    static const Matrix3 Identity;
};

Matrix3 operator*(float scalar, const Matrix3& mat3);

std::ostream& operator<<(std::ostream& os, const Matrix3& mat3);
