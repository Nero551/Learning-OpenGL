#include <catch2/catch_test_macros.hpp>
#include "Utilities/Math/Color.hpp"

TEST_CASE("Color constants") {
   REQUIRE(Color::White == Vector4(1, 1, 1, 1));
   REQUIRE(Color::Black == Vector4(0, 0, 0, 1));
   REQUIRE(Color::Red == Vector4(1, 0, 0, 1));
   REQUIRE(Color::Green == Vector4(0, 1, 0, 1));
   REQUIRE(Color::Blue == Vector4(0, 0, 1, 1));
   REQUIRE(Color::Transparent == Vector4(0, 0, 0, 0));
}