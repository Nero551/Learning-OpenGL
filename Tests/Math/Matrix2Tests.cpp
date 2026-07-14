#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include "Utilities/Math/Matrix/Matrix2.hpp"

using Catch::Matchers::WithinRel;

TEST_CASE("Matrix2 construction and constants") {
   Matrix2 m(2.0f);
   REQUIRE(m.m[0][0] == 2.0f);
   REQUIRE(m.m[0][1] == 2.0f);
   REQUIRE(m.m[1][0] == 2.0f);
   REQUIRE(m.m[1][1] == 2.0f);

   Matrix2 m2(1, 2, 3, 4);
   REQUIRE(m2.m[0][0] == 1);
   REQUIRE(m2.m[0][1] == 2);
   REQUIRE(m2.m[1][0] == 3);
   REQUIRE(m2.m[1][1] == 4);

   REQUIRE(Matrix2::Zero == Matrix2(0));
   REQUIRE(Matrix2::Identity == Matrix2(1, 0, 0, 1));
}

TEST_CASE("Matrix2 arithmetic") {
   Matrix2 A(1, 2, 3, 4);
   Matrix2 B(5, 6, 7, 8);

   SECTION("addition") {
      REQUIRE(A + B == Matrix2(6, 8, 10, 12));
      A += B;
      REQUIRE(A == Matrix2(6, 8, 10, 12));
   }

   SECTION("subtraction") {
      REQUIRE(A - B == Matrix2(-4, -4, -4, -4));
      A -= B;
      REQUIRE(A == Matrix2(-4, -4, -4, -4));
   }

   SECTION("multiplication") {
      REQUIRE(A * B == Matrix2(19, 22, 43, 50));
      A *= B;
      REQUIRE(A == Matrix2(19, 22, 43, 50));
   }

   SECTION("scalar ops") {
      REQUIRE(A * 2.0f == Matrix2(2, 4, 6, 8));
      REQUIRE(A / 2.0f == Matrix2(0.5f, 1, 1.5f, 2));
      REQUIRE(A * 2.0f == 2.0f * A);
      A *= 2;
      REQUIRE(A == Matrix2(2, 4, 6, 8));
      A /= 2;
      REQUIRE(A == Matrix2(1, 2, 3, 4));
   }

   SECTION("unary negation") {
      REQUIRE(-A == Matrix2(-1, -2, -3, -4));
   }

   SECTION("matrix‑vector multiplication") {
      Vector2 v(1, 2);
      REQUIRE(A * v == Vector2(5, 11));
   }

   SECTION("equality") {
      REQUIRE(A == A);
      REQUIRE(A != B);
      REQUIRE(Matrix2::Identity == Matrix2(1, 0, 0, 1));
   }
}

TEST_CASE("Matrix2 methods") {
   Matrix2 A(1, 2, 3, 4);
   Matrix2 I = Matrix2::Identity;

   SECTION("transpose") {
      Matrix2 T = A.Transpose();
      REQUIRE(T == Matrix2(1, 3, 2, 4));
   }

   SECTION("determinant") {
      REQUIRE(A.Determinant() == -2);
      REQUIRE(I.Determinant() == 1);
      Matrix2 singular(1, 2, 2, 4);
      REQUIRE(singular.Determinant() == 0);
   }

   SECTION("inverse") {
      Matrix2 inv = A.Inverse();
      Matrix2 expected = Matrix2(4, -2, -3, 1) / (-2);
      REQUIRE(inv == expected);
      REQUIRE(A * inv == Matrix2::Identity);
      REQUIRE(inv * A == Matrix2::Identity);

      Matrix2 singular(1, 2, 2, 4);
      Matrix2 invSing = singular.Inverse();
      REQUIRE(invSing == Matrix2::Identity);
   }

   SECTION("scaling") {
      Matrix2 M = I.Scale(Vector2(2, 3));
      REQUIRE(M == Matrix2(2, 0, 0, 3));
      Vector2 v(1, 1);
      REQUIRE(M * v == Vector2(2, 3));
   }

   SECTION("rotation") {
      float angle = 3.14159f / 2;
      Matrix2 R = I.Rotate(angle);
      // REQUIRE(R.NearlyEquals(Matrix2(0, -1, 1, 0)));
      Vector2 v(1, 0);
      Vector2 result = R * v;
      REQUIRE(result.NearlyEquals(Vector2(0, 1)));
   }

   SECTION("nearly equals") {
      Matrix2 A2(1.000001f, 2.0f, 3.0f, 4.0f);
      REQUIRE(A2.NearlyEquals(A) == true);
      Matrix2 A3(1.0001f, 2.0f, 3.0f, 4.0f);
      REQUIRE(A3.NearlyEquals(A) == false);
   }
}
