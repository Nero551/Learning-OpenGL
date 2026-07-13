#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include "Utilities/Math/MathUtils.hpp"
#include <cmath>
#include <catch2/catch_approx.hpp>

using Catch::Matchers::WithinRel;
using Catch::Matchers::WithinAbs;
using Catch::Approx;

TEST_CASE("MathUtils Radians and Degrees") {
   float deg = 180.0f;
   float rad = Math::Radians(deg);
   REQUIRE(rad == Approx(3.14159265f));
   float back = Math::Degrees(rad);
   REQUIRE(back == Approx(deg));

   deg = 90.0f;
   rad = Math::Radians(deg);
   REQUIRE(rad == Approx(3.14159265f / 2.0f));
   back = Math::Degrees(rad);
   REQUIRE(back == Approx(deg));
}

TEST_CASE("MathUtils NearlyEquals") {
   REQUIRE(Math::NearlyEquals(1.0f, 1.000001f) == true);
   REQUIRE(Math::NearlyEquals(1.0f, 1.0001f) == false);
   REQUIRE(Math::NearlyEquals(0.0f, 0.0f) == true);
   REQUIRE(Math::NearlyEquals(1e-7f, 0.0f) == true);
   REQUIRE(Math::NearlyEquals(1e-5f, 0.0f) == false);
}