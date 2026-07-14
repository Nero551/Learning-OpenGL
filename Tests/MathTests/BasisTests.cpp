#include <catch2/catch_test_macros.hpp>
#include "Utilities/Math/Basis.hpp"

TEST_CASE("Basis GetMatrix and GetInverseMatrix") {
   Basis basis;
   Matrix4 m = basis.GetMatrix();
   REQUIRE(m == Matrix4::Identity);

   Matrix4 inv = basis.GetInverseMatrix();
   REQUIRE(inv == m.Transpose());

   basis.Right = Vector3::Up;
   basis.Up = Vector3::Forward;
   basis.Forward = Vector3::Right;
   m = basis.GetMatrix();
   Matrix4 expected(0, 0, 1, 0,
                    1, 0, 0, 0,
                    0, 1, 0, 0,
                    0, 0, 0, 1);
   REQUIRE(m == expected);
   inv = basis.GetInverseMatrix();
   REQUIRE(inv == expected.Transpose());
   REQUIRE(inv * m == Matrix4::Identity);
   REQUIRE(m * inv == Matrix4::Identity);
}