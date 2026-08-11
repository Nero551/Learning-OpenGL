#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include "Utilities/Math/Matrix/Matrix2.hpp"

using Catch::Matchers::WithinRel;

TEST_CASE("Matrix2 construction and constants") {
    E::M::Matrix2 m(2.0f);
    REQUIRE(m.m[0][0] == 2.0f);
    REQUIRE(m.m[0][1] == 2.0f);
    REQUIRE(m.m[1][0] == 2.0f);
    REQUIRE(m.m[1][1] == 2.0f);

    E::M::Matrix2 m2(1, 2, 3, 4);
    REQUIRE(m2.m[0][0] == 1);
    REQUIRE(m2.m[0][1] == 2);
    REQUIRE(m2.m[1][0] == 3);
    REQUIRE(m2.m[1][1] == 4);

    REQUIRE(E::M::Matrix2::Zero == E::M::Matrix2(0));
    REQUIRE(E::M::Matrix2::Identity == E::M::Matrix2(1, 0, 0, 1));
}

TEST_CASE("Matrix2 arithmetic") {
    E::M::Matrix2 A(1, 2, 3, 4);
    E::M::Matrix2 B(5, 6, 7, 8);

    SECTION("addition") {
        REQUIRE(A + B == E::M::Matrix2(6, 8, 10, 12));
        A += B;
        REQUIRE(A == E::M::Matrix2(6, 8, 10, 12));
    }

    SECTION("subtraction") {
        REQUIRE(A - B == E::M::Matrix2(-4, -4, -4, -4));
        A -= B;
        REQUIRE(A == E::M::Matrix2(-4, -4, -4, -4));
    }

    SECTION("multiplication") {
        REQUIRE(A * B == E::M::Matrix2(19, 22, 43, 50));
        A *= B;
        REQUIRE(A == E::M::Matrix2(19, 22, 43, 50));
    }

    SECTION("scalar ops") {
        REQUIRE(A * 2.0f == E::M::Matrix2(2, 4, 6, 8));
        REQUIRE(A / 2.0f == E::M::Matrix2(0.5f, 1, 1.5f, 2));
        REQUIRE(A * 2.0f == 2.0f * A);
        A *= 2;
        REQUIRE(A == E::M::Matrix2(2, 4, 6, 8));
        A /= 2;
        REQUIRE(A == E::M::Matrix2(1, 2, 3, 4));
    }

    SECTION("unary negation") { REQUIRE(-A == E::M::Matrix2(-1, -2, -3, -4)); }

    SECTION("matrix‑vector multiplication") {
        E::M::Vector2 v(1, 2);
        REQUIRE(A * v == E::M::Vector2(5, 11));
    }

    SECTION("equality") {
        REQUIRE(A == A);
        REQUIRE(A != B);
        REQUIRE(E::M::Matrix2::Identity == E::M::Matrix2(1, 0, 0, 1));
    }
}

TEST_CASE("Matrix2 methods") {
    E::M::Matrix2 A(1, 2, 3, 4);
    E::M::Matrix2 I = E::M::Matrix2::Identity;

    SECTION("transpose") {
        E::M::Matrix2 T = A.Transpose();
        REQUIRE(T == E::M::Matrix2(1, 3, 2, 4));
    }

    SECTION("determinant") {
        REQUIRE(A.Determinant() == -2);
        REQUIRE(I.Determinant() == 1);
        E::M::Matrix2 singular(1, 2, 2, 4);
        REQUIRE(singular.Determinant() == 0);
    }

    SECTION("inverse") {
        E::M::Matrix2 inv = A.Inverse();
        E::M::Matrix2 expected = E::M::Matrix2(4, -2, -3, 1) / -2;
        REQUIRE(inv == expected);
        REQUIRE(A * inv == E::M::Matrix2::Identity);
        REQUIRE(inv * A == E::M::Matrix2::Identity);

        E::M::Matrix2 singular(1, 2, 2, 4);
        E::M::Matrix2 invSing = singular.Inverse();
        REQUIRE(invSing == E::M::Matrix2::Identity);
    }

    SECTION("scaling") {
        E::M::Matrix2 M = I.Scale(E::M::Vector2(2, 3));
        REQUIRE(M == E::M::Matrix2(2, 0, 0, 3));
        E::M::Vector2 v(1, 1);
        REQUIRE(M * v == E::M::Vector2(2, 3));
    }

    SECTION("rotation") {
        float angle = 3.14159f / 2;
        E::M::Matrix2 R = I.Rotate(angle);
        REQUIRE(R.NearlyEquals(E::M::Matrix2(0, -1, 1, 0)));
        E::M::Vector2 v(1, 0);
        E::M::Vector2 result = R * v;
        REQUIRE(result.NearlyEquals(E::M::Vector2(0, 1)));
    }

    SECTION("nearly equals") {
        E::M::Matrix2 A2(1.000001f, 2.0f, 3.0f, 4.0f);
        REQUIRE(A2.NearlyEquals(A) == true);
        E::M::Matrix2 A3(1.0001f, 2.0f, 3.0f, 4.0f);
        REQUIRE(A3.NearlyEquals(A) == false);
    }
}
