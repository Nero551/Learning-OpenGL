#pragma once
#include <iosfwd>

#include "../MathUtils.hpp"

struct Vector3 {
    float x;
    float y;
    float z;

    Vector3();

    Vector3(float all);

    Vector3(float x, float y, float z);

    [[nodiscard]] float LengthSquared() const;

    [[nodiscard]] float Length() const;

    [[nodiscard]] Vector3 Normalized() const;

    [[nodiscard]] float Dot(const Vector3& vec3) const;

    [[nodiscard]] Vector3 Cross(const Vector3& vec3) const;

    [[nodiscard]] float Distance(const Vector3& vec3) const;

    [[nodiscard]] bool NearlyEquals(const Vector3& vec3, float epsilon = Math::EPSILONF) const;

    [[nodiscard]] bool IsParallelTo(const Vector3& vec3) const;

    [[nodiscard]] bool IsPerpendicularTo(const Vector3& vec3) const;

    Vector3 operator+(const Vector3& vec3) const;

    Vector3 operator-(const Vector3& vec3) const;

    Vector3 operator*(const Vector3& vec3) const;

    Vector3& operator+=(const Vector3& vec3);

    Vector3& operator-=(const Vector3& vec3);

    Vector3& operator*=(const Vector3& vec3);

    Vector3 operator+(float scalar) const;

    Vector3 operator-(float scalar) const;

    Vector3 operator*(float scalar) const;

    Vector3 operator/(float scalar) const;

    Vector3& operator+=(float scalar);

    Vector3& operator-=(float scalar);

    Vector3& operator*=(float scalar);

    Vector3& operator/=(float scalar);

    Vector3 operator-() const;

    bool operator==(const Vector3& vec3) const;

    bool operator!=(const Vector3& vec3) const;

    static const Vector3 Zero;
    static const Vector3 One;
    static const Vector3 Up;
    static const Vector3 Right;
    static const Vector3 Forward;
};

Vector3 operator+(float scalar, const Vector3& vec3);

Vector3 operator-(float scalar, const Vector3& vec3);

Vector3 operator*(float scalar, const Vector3& vec3);

Vector3 operator/(float scalar, const Vector3& vec3);

std::ostream& operator<<(std::ostream& os, const Vector3& vec3);
