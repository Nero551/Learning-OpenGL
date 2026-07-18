#pragma once

#include "../MathUtils.hpp"

struct Vector2 {
    float x;
    float y;

    Vector2();

    Vector2(float all);

    Vector2(float x, float y);

    [[nodiscard]] float LengthSquared() const;

    [[nodiscard]] float Length() const;

    [[nodiscard]] Vector2 Normalized() const;

    [[nodiscard]] float Dot(const Vector2& vec2) const;

    [[nodiscard]] float Distance(const Vector2& vec2) const;

    [[nodiscard]] bool NearlyEquals(const Vector2& vec2, float epsilon = Math::EPSILONF) const;

    Vector2 operator+(const Vector2& vec2) const;

    Vector2 operator-(const Vector2& vec2) const;

    Vector2 operator*(const Vector2& vec2) const;

    Vector2& operator+=(const Vector2& vec2);

    Vector2& operator-=(const Vector2& vec2);

    Vector2& operator*=(const Vector2& vec2);

    Vector2 operator+(float scalar) const;

    Vector2 operator-(float scalar) const;

    Vector2 operator*(float scalar) const;

    Vector2 operator/(float scalar) const;

    Vector2& operator+=(float scalar);

    Vector2& operator-=(float scalar);

    Vector2& operator*=(float scalar);

    Vector2& operator/=(float scalar);

    Vector2 operator-() const;

    bool operator==(const Vector2& vec2) const;

    bool operator!=(const Vector2& vec2) const;

    static const Vector2 Zero;
};

Vector2 operator+(float scalar, const Vector2& vec2);

Vector2 operator-(float scalar, const Vector2& vec2);

Vector2 operator*(float scalar, const Vector2& vec2);

Vector2 operator/(float scalar, const Vector2& vec2);

std::ostream& operator<<(std::ostream& os, const Vector2& vec2);
