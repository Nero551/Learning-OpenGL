#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include "Utilities/Math/Vector/Vector3.hpp"
#include <cmath>
#include <catch2/catch_approx.hpp>

using Catch::Matchers::WithinRel;
using Catch::Matchers::WithinAbs;
using Catch::Approx;

TEST_CASE("Vector3 construction and constants") {
    E::M::Vector3 v(1.0f, 2.0f, 3.0f);
    REQUIRE(v.x == 1.0f);
    REQUIRE(v.y == 2.0f);
    REQUIRE(v.z == 3.0f);

    REQUIRE(E::M::Vector3::Zero == E::M::Vector3(0, 0, 0));
    REQUIRE(E::M::Vector3::One == E::M::Vector3(1, 1, 1));
    REQUIRE(E::M::Vector3::Right == E::M::Vector3(1, 0, 0));
    REQUIRE(E::M::Vector3::Up == E::M::Vector3(0, 1, 0));
    REQUIRE(E::M::Vector3::Forward == E::M::Vector3(0, 0, 1));
}

TEST_CASE("Vector3 addition") {
    E::M::Vector3 a(1, 2, 3);
    E::M::Vector3 b(4, 5, 6);
    REQUIRE(a + b == E::M::Vector3(5, 7, 9));
    a += b;
    REQUIRE(a == E::M::Vector3(5, 7, 9));
}

TEST_CASE("Vector3 component‑wise multiplication") {
    E::M::Vector3 a(1, 2, 3);
    E::M::Vector3 b(4, 5, 6);
    REQUIRE(a * b == E::M::Vector3(4, 10, 18));
    a *= b;
    REQUIRE(a == E::M::Vector3(4, 10, 18));
}

TEST_CASE("Vector3 dot product") {
    E::M::Vector3 a(1, 2, 3);
    E::M::Vector3 b(4, 5, 6);
    REQUIRE(a.Dot(b) == 32);
    REQUIRE(a.Dot(E::M::Vector3::Zero) == 0);
    REQUIRE(E::M::Vector3::Right.Dot(E::M::Vector3::Up) == 0);
}

TEST_CASE("Vector3 cross product") {
    E::M::Vector3 i(1, 0, 0);
    E::M::Vector3 j(0, 1, 0);
    E::M::Vector3 k(0, 0, 1);
    REQUIRE(i.Cross(j) == k);
    REQUIRE(j.Cross(i) == -k);
    REQUIRE(i.Cross(k) == -j);
    REQUIRE(k.Cross(i) == j);

    E::M::Vector3 a(2, 3, 4);
    E::M::Vector3 b(5, 6, 7);
    E::M::Vector3 expected(3 * 7 - 4 * 6, 4 * 5 - 2 * 7, 2 * 6 - 3 * 5);
    REQUIRE(a.Cross(b) == expected);
    REQUIRE(a.Cross(a) == E::M::Vector3::Zero);
}

TEST_CASE("Vector3 scalar and unary operations") {
    E::M::Vector3 a(1, -2, 3);
    REQUIRE(a + 2.0f == E::M::Vector3(3, 0, 5));
    REQUIRE(a * 2.0f == E::M::Vector3(2, -4, 6));
    REQUIRE(a / 2.0f == E::M::Vector3(0.5f, -1, 1.5f));
    REQUIRE(-a == E::M::Vector3(-1, 2, -3));
    REQUIRE(5.0f - a == E::M::Vector3(4, 7, 2));
    REQUIRE(10.0f / a == E::M::Vector3(10, -5, 10.0f / 3.0f));
}

TEST_CASE("Vector3 length, normalization, distance") {
    E::M::Vector3 a(3, 4, 0);
    REQUIRE(a.Length() == 5.0f);
    REQUIRE(a.LengthSquared() == 25.0f);
    E::M::Vector3 n = a.Normalized();
    REQUIRE(n == E::M::Vector3(0.6f, 0.8f, 0.0f));
    REQUIRE(n.Length() == Approx(1.0f));

    E::M::Vector3 b(1, 1, 1);
    REQUIRE(b.Length() == Approx(std::sqrt(3.0f)));

    REQUIRE(a.Distance(b) == Approx(std::sqrt(14.0f)));

    E::M::Vector3 zero = E::M::Vector3::Zero;
    REQUIRE(zero.Normalized() == E::M::Vector3::Zero);
}

TEST_CASE("Vector3 parallel and perpendicular") {
    E::M::Vector3 a(1, 2, 3);
    E::M::Vector3 b(2, 4, 6);
    E::M::Vector3 c(1, 0, 0);
    E::M::Vector3 d(0, 1, 0);
    E::M::Vector3 e(1, 1, 1);

    REQUIRE(a.IsParallelTo(b) == true);
    REQUIRE(a.IsParallelTo(-b) == true);
    REQUIRE(a.IsParallelTo(c) == false);
    REQUIRE(E::M::Vector3::Zero.IsParallelTo(a) == false);
    REQUIRE(c.IsPerpendicularTo(d) == true);
    REQUIRE(c.IsPerpendicularTo(e) == false);
    REQUIRE(E::M::Vector3::Zero.IsPerpendicularTo(c) == false);
}

TEST_CASE("Vector3 nearly equals") {
    E::M::Vector3 a(1.000001f, 2.000001f, 3.000001f);
    E::M::Vector3 b(1.0001f, 2.0f, 3.0f);
    REQUIRE(a.NearlyEquals(E::M::Vector3(1, 2, 3)) == true);
    REQUIRE(b.NearlyEquals(E::M::Vector3(1, 2, 3)) == false);
}