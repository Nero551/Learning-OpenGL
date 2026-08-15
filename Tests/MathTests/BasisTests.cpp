#include <catch2/catch_test_macros.hpp>
#include "Math/Geometry/Basis.hpp"

TEST_CASE (


"Basis GetMatrix and GetInverseMatrix"
)
 {
   E::M::Basis basis;
   E::M::Matrix4 m = basis.GetMatrix();
   REQUIRE(m == E::M::Matrix4::Identity);

   E::M::Matrix4 inv = basis.GetInverseMatrix();
   REQUIRE(inv == m.Transpose());

   basis.Right = E::M::Vector3::Up;
   basis.Up = E::M::Vector3::Forward;
   basis.Forward = E::M::Vector3::Right;
   m = basis.GetMatrix();
   E::M::Matrix4 expected(0, 0, 1, 0,
                    1, 0, 0, 0,
                    0, 1, 0, 0,
                    0, 0, 0, 1);
   REQUIRE(m == expected);
   inv = basis.GetInverseMatrix();
   REQUIRE(inv == expected.Transpose());
   REQUIRE(inv * m == E::M::Matrix4::Identity);
   REQUIRE(m * inv == E::M::Matrix4::Identity);
}