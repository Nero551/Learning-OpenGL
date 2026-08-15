#include <catch2/catch_test_macros.hpp>
#include "Math/Color/Color.hpp"

TEST_CASE (


"Color constants"
)
 {
   REQUIRE(E::M::Color::White == E::M::Vector4(1, 1, 1, 1));
   REQUIRE(E::M::Color::Black == E::M::Vector4(0, 0, 0, 1));
   REQUIRE(E::M::Color::Red == E::M::Vector4(1, 0, 0, 1));
   REQUIRE(E::M::Color::Green == E::M::Vector4(0, 1, 0, 1));
   REQUIRE(E::M::Color::Blue == E::M::Vector4(0, 0, 1, 1));
   REQUIRE(E::M::Color::Transparent == E::M::Vector4(0, 0, 0, 0));
}