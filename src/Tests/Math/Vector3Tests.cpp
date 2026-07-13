#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include "Utilities/Math/Vector/Vector3.hpp"
#include <cmath>
#include <catch2/catch_approx.hpp>

using Catch::Matchers::WithinRel;
using Catch::Matchers::WithinAbs;
using Catch::Approx;

TEST_CASE("Vector3 construction and constants") {
    Vector3 v(1.0f, 2.0f, 3.0f);
    REQUIRE(v.x == 1.0f);
    REQUIRE(v.y == 2.0f);
    REQUIRE(v.z == 3.0f);

    REQUIRE(Vector3::Zero == Vector3(0, 0, 0));
    REQUIRE(Vector3::One == Vector3(1, 1, 1));
    REQUIRE(Vector3::Right == Vector3(1, 0, 0));
    REQUIRE(Vector3::Up == Vector3(0, 1, 0));
    REQUIRE(Vector3::Forward == Vector3(0, 0, 1));
}

TEST_CASE("Vector3 addition") {
    Vector3 a(1, 2, 3);
    Vector3 b(4, 5, 6);
    REQUIRE(a + b == Vector3(5, 7, 9));
    a += b;
    REQUIRE(a == Vector3(5, 7, 9));
}

TEST_CASE("Vector3 component‑wise multiplication") {
    Vector3 a(1, 2, 3);
    Vector3 b(4, 5, 6);
    REQUIRE(a * b == Vector3(4, 10, 18));
    a *= b;
    REQUIRE(a == Vector3(4, 10, 18));
}

TEST_CASE("Vector3 dot product") {
    Vector3 a(1, 2, 3);
    Vector3 b(4, 5, 6);
    REQUIRE(a.Dot(b) == 32);
    REQUIRE(a.Dot(Vector3::Zero) == 0);
    REQUIRE(Vector3::Right.Dot(Vector3::Up) == 0);
}

TEST_CASE("Vector3 cross product") {
    Vector3 i(1, 0, 0);
    Vector3 j(0, 1, 0);
    Vector3 k(0, 0, 1);
    REQUIRE(i.Cross(j) == k);
    REQUIRE(j.Cross(i) == -k);
    REQUIRE(i.Cross(k) == -j);
    REQUIRE(k.Cross(i) == j);

    Vector3 a(2, 3, 4);
    Vector3 b(5, 6, 7);
    Vector3 expected(3 * 7 - 4 * 6, 4 * 5 - 2 * 7, 2 * 6 - 3 * 5);
    REQUIRE(a.Cross(b) == expected);
    REQUIRE(a.Cross(a) == Vector3::Zero);
}

TEST_CASE("Vector3 scalar and unary operations") {
    Vector3 a(1, -2, 3);
    REQUIRE(a + 2.0f == Vector3(3, 0, 5));
    REQUIRE(a * 2.0f == Vector3(2, -4, 6));
    REQUIRE(a / 2.0f == Vector3(0.5f, -1, 1.5f));
    REQUIRE(-a == Vector3(-1, 2, -3));
    REQUIRE(5.0f - a == Vector3(4, 7, 2));
    REQUIRE(10.0f / a == Vector3(10, -5, 10.0f / 3.0f));
}

TEST_CASE("Vector3 length, normalization, distance") {
    Vector3 a(3, 4, 0);
    REQUIRE(a.Length() == 5.0f);
    REQUIRE(a.LengthSquared() == 25.0f);
    Vector3 n = a.Normalized();
    REQUIRE(n == Vector3(0.6f, 0.8f, 0.0f));
    REQUIRE(n.Length() == Approx(1.0f));

    Vector3 b(1, 1, 1);
    REQUIRE(b.Length() == Approx(std::sqrt(3.0f)));

    REQUIRE(a.Distance(b) == Approx(std::sqrt(14.0f)));

    Vector3 zero = Vector3::Zero;
    REQUIRE(zero.Normalized() == Vector3::Zero);
}

TEST_CASE("Vector3 parallel and perpendicular") {
    Vector3 a(1, 2, 3);
    Vector3 b(2, 4, 6);
    Vector3 c(1, 0, 0);
    Vector3 d(0, 1, 0);
    Vector3 e(1, 1, 1);

    REQUIRE(a.IsParallelTo(b) == true);
    REQUIRE(a.IsParallelTo(-b) == true);
    REQUIRE(a.IsParallelTo(c) == false);
    REQUIRE(Vector3::Zero.IsParallelTo(a) == false);
    REQUIRE(c.IsPerpendicularTo(d) == true);
    REQUIRE(c.IsPerpendicularTo(e) == false);
    REQUIRE(Vector3::Zero.IsPerpendicularTo(c) == false);
}

TEST_CASE("Vector3 nearly equals") {
    Vector3 a(1.000001f, 2.000001f, 3.000001f);
    Vector3 b(1.0001f, 2.0f, 3.0f);
    REQUIRE(a.NearlyEquals(Vector3(1, 2, 3)) == true);
    REQUIRE(b.NearlyEquals(Vector3(1, 2, 3)) == false);
}