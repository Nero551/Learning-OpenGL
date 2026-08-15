#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include "Math/Matrix/Matrix3.hpp"

using Catch::Matchers::WithinRel;

TEST_CASE (


"Matrix3 construction and constants"
)
 {
    E::M::Matrix3 m(2);
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            REQUIRE(m.m[i][j] == 2.0f);

    E::M::Matrix3 m2(1, 2, 3, 4, 5, 6, 7, 8, 9);
    REQUIRE(m2.m[0][1] == 2);
    REQUIRE(m2.m[1][2] == 6);
    REQUIRE(m2.m[2][0] == 7);

    REQUIRE(E::M::Matrix3::Zero == E::M::Matrix3(0));
    REQUIRE(E::M::Matrix3::Identity == E::M::Matrix3(1, 0, 0, 0, 1, 0, 0, 0, 1));
}

TEST_CASE (


"Matrix3 arithmetic"
)
 {
    E::M::Matrix3 A(1, 2, 3, 4, 5, 6, 7, 8, 9);
    E::M::Matrix3 B(9, 8, 7, 6, 5, 4, 3, 2, 1);
    E::M::Vector3 v(1, 2, 3);

    REQUIRE(A + B == E::M::Matrix3(10, 10, 10, 10, 10, 10, 10, 10, 10));
    A += B;
    REQUIRE(A == E::M::Matrix3(10, 10, 10, 10, 10, 10, 10, 10, 10));

    REQUIRE(A - B == E::M::Matrix3(1, 2, 3, 4, 5, 6, 7, 8, 9));
    A -= B;
    REQUIRE(A == E::M::Matrix3(1, 2, 3, 4, 5, 6, 7, 8, 9));

    REQUIRE(A * E::M::Matrix3::Identity == A);
    REQUIRE(E::M::Matrix3::Identity * A == A);

    REQUIRE(A * v == E::M::Vector3(14, 32, 50));

    REQUIRE(A * 2.0f == E::M::Matrix3(2, 4, 6, 8, 10, 12, 14, 16, 18));
    REQUIRE(A / 2.0f == E::M::Matrix3(0.5f, 1, 1.5f, 2, 2.5f, 3, 3.5f, 4, 4.5f));
    REQUIRE(A * 2.0f == 2.0f * A);
    A *= 2;
    REQUIRE(A == E::M::Matrix3(2, 4, 6, 8, 10, 12, 14, 16, 18));
    A /= 2;
    REQUIRE(A == E::M::Matrix3(1, 2, 3, 4, 5, 6, 7, 8, 9));

    REQUIRE(-A == E::M::Matrix3(-1, -2, -3, -4, -5, -6, -7, -8, -9));
}

TEST_CASE (


"Matrix3 methods"
)
 {
    E::M::Matrix3 I = E::M::Matrix3::Identity;
    E::M::Matrix3 A(1, 2, 3, 4, 5, 6, 7, 8, 9);

    SECTION("transpose") {
        E::M::Matrix3 T = A.Transpose();
        REQUIRE(T == E::M::Matrix3(1, 4, 7, 2, 5, 8, 3, 6, 9));
    }

    SECTION("determinant") {
        REQUIRE(I.Determinant() == 1);
        REQUIRE(A.Determinant() == 0);
        E::M::Matrix3 B(1, 0, 0, 0, 1, 0, 0, 0, 1);
        REQUIRE(B.Determinant() == 1);
        E::M::Matrix3 C(1, 2, 3, 0, 1, 4, 0, 0, 1);
        REQUIRE(C.Determinant() == 1);
    }

    SECTION("inverse") {
        E::M::Matrix3 M(4, 7, 2, 3, 1, 5, 8, 6, 9);
        E::M::Matrix3 inv = M.Inverse();
        REQUIRE((M * inv).NearlyEquals(E::M::Matrix3::Identity) );
        REQUIRE((inv * M).NearlyEquals( E::M::Matrix3::Identity));

        E::M::Matrix3 singular(1, 2, 3, 4, 5, 6, 7, 8, 9);
        REQUIRE(singular.Inverse() == E::M::Matrix3::Identity);
    }

    SECTION("minor") {
        E::M::Matrix3 A(1, 2, 3, 4, 5, 6, 7, 8, 9);
        E::M::Matrix2 minor00 = A.Minor(0, 0);
        REQUIRE(minor00 == E::M::Matrix2(5, 6, 8, 9));
        E::M::Matrix2 minor01 = A.Minor(0, 1);
        REQUIRE(minor01 == E::M::Matrix2(4, 6, 7, 9));
        E::M::Matrix2 minor02 = A.Minor(0, 2);
        REQUIRE(minor02 == E::M::Matrix2(4, 5, 7, 8));
    }

    SECTION("scaling") {
        E::M::Matrix3 S = I.Scale(E::M::Vector3(2, 3, 4));
        REQUIRE(S == E::M::Matrix3(2, 0, 0, 0, 3, 0, 0, 0, 4));
        E::M::Vector3 v(1, 2, 3);
        REQUIRE(S * v == E::M::Vector3(2, 6, 12));
    }

    SECTION("translation") {
        E::M::Matrix3 T = I.Translate(E::M::Vector2(5, 6));
        REQUIRE(T == E::M::Matrix3(1, 0, 5, 0, 1, 6, 0, 0, 1));
        E::M::Vector3 v(1, 2, 1);
        REQUIRE(T * v == E::M::Vector3(6, 8, 1));
    }

    SECTION("rotation about axes") {
        float angle = 3.14159f / 2;
        E::M::Matrix3 Rx = I.RotateX(angle);
        E::M::Vector3 v(0, 1, 0);
        E::M::Vector3 result = Rx * v;
        REQUIRE(result.NearlyEquals(E::M::Vector3(0, 0, 1)));

        E::M::Matrix3 Ry = I.RotateY(angle);
        E::M::Vector3 u(1, 0, 0);
        E::M::Vector3 resY = Ry * u;
        REQUIRE(resY.NearlyEquals(E::M::Vector3(0, 0, -1)));

        E::M::Matrix3 Rz = I.RotateZ(angle);
        E::M::Vector3 w(1, 0, 0);
        E::M::Vector3 resZ = Rz * w;
        REQUIRE(resZ.NearlyEquals(E::M::Vector3(0, 1, 0)));
    }

    SECTION("rotate around arbitrary axis") {
        E::M::Vector3 axis = E::M::Vector3::Up;
        float angle = 3.14159f / 2;
        E::M::Matrix3 R1 = I.RotateAroundAxis(axis, angle);
        E::M::Matrix3 R2 = I.RotateY(angle);
        REQUIRE(R1.NearlyEquals(R2));

        axis = E::M::Vector3::Forward;
        R1 = I.RotateAroundAxis(axis, angle);
        R2 = I.RotateZ(angle);
        REQUIRE(R1.NearlyEquals(R2));
    }

    SECTION("nearly equals") {
        E::M::Matrix3 A2(1.000001f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f);
        REQUIRE(A2.NearlyEquals(A) == true);
        E::M::Matrix3 A3(1.0001f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f);
        REQUIRE(A3.NearlyEquals(A) == false);
    }
}