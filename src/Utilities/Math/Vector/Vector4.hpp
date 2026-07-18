#pragma once
#include <iosfwd>

#include "../MathUtils.hpp"

struct Vector4 {
    float x;
    float y;
    float z;
    float w;

    Vector4();

    Vector4(float all);

    Vector4(float x, float y, float z, float w);

    [[nodiscard]] float LengthSquared() const;

    [[nodiscard]] float Length() const;

    [[nodiscard]] Vector4 Normalized() const;

    [[nodiscard]] float Dot(const Vector4& vec4) const;

    [[nodiscard]] float Distance(const Vector4& vec4) const;

    [[nodiscard]] bool NearlyEquals(const Vector4& vec4, float epsilon = Math::EPSILONF) const;

    Vector4 operator+(const Vector4& vec4) const;

    Vector4 operator-(const Vector4& vec4) const;

    Vector4 operator*(const Vector4& vec4) const;

    Vector4& operator+=(const Vector4& vec4);

    Vector4& operator-=(const Vector4& vec4);

    Vector4& operator*=(const Vector4& vec4);

    Vector4 operator+(float scalar) const;

    Vector4 operator-(float scalar) const;

    Vector4 operator*(float scalar) const;

    Vector4 operator/(float scalar) const;

    Vector4& operator+=(float scalar);

    Vector4& operator-=(float scalar);

    Vector4& operator*=(float scalar);

    Vector4& operator/=(float scalar);

    Vector4 operator-() const;

    bool operator==(const Vector4& vec4) const;

    bool operator!=(const Vector4& vec4) const;

    static const Vector4 Zero;
};

Vector4 operator+(float scalar, const Vector4& vec4);

Vector4 operator-(float scalar, const Vector4& vec4);

Vector4 operator*(float scalar, const Vector4& vec4);

Vector4 operator/(float scalar, const Vector4& vec4);

std::ostream& operator<<(std::ostream& os, const Vector4& vec4);
