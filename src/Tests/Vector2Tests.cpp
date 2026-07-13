#include <catch2/catch_test_macros.hpp>
#include "Utilities/Math/Vector/Vector3.hpp"

TEST_CASE("Vector addition") {
   Vector3 a(1, 2, 3);
   Vector3 b(4, 5, 6);

   REQUIRE(a + b == Vector3(5,7,9));
}

TEST_CASE("Vector Multiplication") {
   Vector3 a(1, 2, 3);
   Vector3 b(4, 5, 6);
   REQUIRE(a * b == Vector3(4,10,18));
}

TEST_CASE("Vector Dot Product") {
   Vector3 a(1, 2, 3);
   Vector3 b(4, 5, 6);
   REQUIRE(a.Dot(b) == 32);
}