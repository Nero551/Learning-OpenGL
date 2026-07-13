#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include "Utilities/Math/Vector/Vector4.hpp"
#include <cmath>
#include <catch2/catch_approx.hpp>

using Catch::Matchers::WithinRel;
using Catch::Matchers::WithinAbs;
using Catch::Approx;

TEST_CASE("Vector4 construction") {
   Vector4 v(1, 2, 3, 4);
   REQUIRE(v.x == 1);
   REQUIRE(v.y == 2);
   REQUIRE(v.z == 3);
   REQUIRE(v.w == 4);
   Vector4 all(5);
   REQUIRE(all == Vector4(5, 5, 5, 5));
   REQUIRE(Vector4::Zero == Vector4(0, 0, 0, 0));
}

TEST_CASE("Vector4 arithmetic") {
   Vector4 a(1, 2, 3, 4);
   Vector4 b(5, 6, 7, 8);
   REQUIRE(a + b == Vector4(6, 8, 10, 12));
   REQUIRE(a - b == Vector4(-4, -4, -4, -4));
   REQUIRE(a * b == Vector4(5, 12, 21, 32));
   REQUIRE(a * 2.0f == Vector4(2, 4, 6, 8));
   REQUIRE(2.0f * a == Vector4(2, 4, 6, 8));
   REQUIRE(a / 2.0f == Vector4(0.5f, 1, 1.5f, 2));
}

TEST_CASE("Vector4 dot, length, normalization") {
   Vector4 a(1, 2, 3, 4);
   REQUIRE(a.Dot(a) == 30);
   REQUIRE(a.LengthSquared() == 30);
   REQUIRE(a.Length() == Approx(std::sqrt(30)));
   Vector4 n = a.Normalized();
   REQUIRE(n.Length() == Approx(1.0f));
   REQUIRE(n.NearlyEquals(Vector4(1, 2, 3, 4) / std::sqrt(30)));
   Vector4 zero = Vector4::Zero;
   REQUIRE(zero.Normalized() == Vector4::Zero);
}