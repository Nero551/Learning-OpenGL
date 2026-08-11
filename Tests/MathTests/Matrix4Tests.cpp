#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include "Utilities/Math/Matrix/Matrix4.hpp"
#include <catch2/catch_approx.hpp>


using Catch::Matchers::WithinRel;
using Catch::Matchers::WithinAbs;
using Catch::Approx;

TEST_CASE("Matrix4 construction and constants") {
    E::M::Matrix4 m(2);
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            REQUIRE(m.m[i][j] == 2.0f);

    E::M::Matrix4 m2(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    REQUIRE(m2.m[0][3] == 4);
    REQUIRE(m2.m[3][0] == 13);

    REQUIRE(E::M::Matrix4::Zero == E::M::Matrix4(0));
    REQUIRE(E::M::Matrix4::Identity == E::M::Matrix4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1));
}

TEST_CASE("Matrix4 arithmetic") {
    E::M::Matrix4 A = E::M::Matrix4::Identity;
    E::M::Matrix4 B(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    E::M::Vector4 v(1, 2, 3, 4);

    REQUIRE(A + B == E::M::Matrix4(2, 2, 3, 4, 5, 7, 7, 8, 9, 10, 12, 12, 13, 14, 15, 17));
    REQUIRE(A - B == E::M::Matrix4(0, -2, -3, -4, -5, -5, -7, -8, -9, -10, -10, -12, -13, -14, -15, -15));

    REQUIRE(A * B == B);
    REQUIRE(B * A == B);

    REQUIRE(B * v == E::M::Vector4(30, 70, 110, 150));

    REQUIRE(B * 2.0f == E::M::Matrix4(2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32));
    REQUIRE(B / 2.0f == E::M::Matrix4(0.5f, 1, 1.5f, 2, 2.5f, 3, 3.5f, 4, 4.5f, 5, 5.5f, 6, 6.5f, 7, 7.5f, 8));
    REQUIRE(B * 2.0f == 2.0f * B);
    B *= 2;
    REQUIRE(B == E::M::Matrix4(2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32));
    B /= 2;
    REQUIRE(B == E::M::Matrix4(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16));

    REQUIRE(-A == E::M::Matrix4(-1, 0, 0, 0, 0, -1, 0, 0, 0, 0, -1, 0, 0, 0, 0, -1));
}

TEST_CASE("Matrix4 methods") {
    E::M::Matrix4 I = E::M::Matrix4::Identity;
    E::M::Matrix4 A(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);

    SECTION("transpose") {
        E::M::Matrix4 T = A.Transpose();
        REQUIRE(T.m[0][1] == A.m[1][0]);
        REQUIRE(T.m[1][2] == A.m[2][1]);
    }

    SECTION("determinant") {
        REQUIRE(I.Determinant() == 1);
        REQUIRE(A.Determinant() == 0);
        E::M::Matrix4 B(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
        REQUIRE(B.Determinant() == 1);
    }

    SECTION("inverse") {
        REQUIRE(I.Inverse() == I);
        E::M::Matrix4 S = I.Scale(E::M::Vector3(2, 3, 4));
        E::M::Matrix4 T = I.Translate(E::M::Vector3(1, 2, 3));
        E::M::Matrix4 M2 = T * S;
        E::M::Matrix4 inv = M2.Inverse();
        REQUIRE(M2 * inv == E::M::Matrix4::Identity);
        REQUIRE(inv * M2 == E::M::Matrix4::Identity);

        E::M::Matrix4 singular(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
        REQUIRE(singular.Inverse() == E::M::Matrix4::Identity);
    }

    SECTION("minor") {
        E::M::Matrix4 A(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
        E::M::Matrix3 minor00 = A.Minor(0, 0);
        REQUIRE(minor00 == E::M::Matrix3(6, 7, 8, 10, 11, 12, 14, 15, 16));
    }

    SECTION("scaling") {
        E::M::Matrix4 S = I.Scale(E::M::Vector3(2, 3, 4));
        REQUIRE(S == E::M::Matrix4(2, 0, 0, 0, 0, 3, 0, 0, 0, 0, 4, 0, 0, 0, 0, 1));
        E::M::Vector4 v(1, 2, 3, 1);
        REQUIRE(S * v == E::M::Vector4(2, 6, 12, 1));
    }

    SECTION("translation") {
        E::M::Matrix4 T = I.Translate(E::M::Vector3(5, 6, 7));
        REQUIRE(T == E::M::Matrix4(1, 0, 0, 5, 0, 1, 0, 6, 0, 0, 1, 7, 0, 0, 0, 1));
        E::M::Vector4 v(1, 2, 3, 1);
        REQUIRE(T * v == E::M::Vector4(6, 8, 10, 1));
    }

    SECTION("rotation about axes") {
        float angle = 3.14159f / 2;
        E::M::Matrix4 Rx = I.RotateX(angle);
        E::M::Vector4 v(0, 1, 0, 1);
        E::M::Vector4 result = Rx * v;
        REQUIRE(result.NearlyEquals(E::M::Vector4(0, 0, 1, 1)));

        E::M::Matrix4 Ry = I.RotateY(angle);
        E::M::Vector4 u(1, 0, 0, 1);
        E::M::Vector4 resY = Ry * u;
        REQUIRE(resY.NearlyEquals(E::M::Vector4(0, 0, -1, 1)));

        E::M::Matrix4 Rz = I.RotateZ(angle);
        E::M::Vector4 w(1, 0, 0, 1);
        E::M::Vector4 resZ = Rz * w;
        REQUIRE(resZ.NearlyEquals(E::M::Vector4(0, 1, 0, 1)));
    }

    SECTION("rotate around axis") {
        E::M::Vector3 axis = E::M::Vector3::Up;
        float angle = 3.14159f / 2;
        E::M::Matrix4 R1 = I.RotateAroundAxis(axis, angle);
        E::M::Matrix4 R2 = I.RotateY(angle);
        REQUIRE(R1.NearlyEquals(R2));
    }

    SECTION("ToMatrix3") {
        E::M::Matrix4 M(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
        E::M::Matrix3 M3 = M.ToMatrix3();
        REQUIRE(M3 == E::M::Matrix3(1, 2, 3, 5, 6, 7, 9, 10, 11));
    }

    SECTION("Orthographic projection") {
        float l = -1, r = 1, b = -1, t = 1, n = 0.1f, f = 100;
        E::M::Matrix4 proj = E::M::Matrix4::Orthographic(l, r, b, t, n, f);
        E::M::Vector4 p(0, 0, -1, 1);
        E::M::Vector4 result = proj * p;
        REQUIRE(result.x == 0);
        REQUIRE(result.y == 0);
        REQUIRE(result.z == Approx((2 - f - n) / (f - n)));
        REQUIRE(result.w == 1);
    }

    SECTION("Perspective projection") {
        float fov = 3.14159f / 4;
        float aspect = 16.0f / 9.0f;
        float near = 0.1f, far = 100;
        E::M::Matrix4 proj = E::M::Matrix4::Perspective(fov, aspect, near, far);
        E::M::Vector4 p(0, 0, -near, 1);
        E::M::Vector4 result = proj * p;
        REQUIRE(result.x == 0);
        REQUIRE(result.y == 0);
        REQUIRE(result.z == Approx(-near));
        REQUIRE(result.w == Approx(near));
        REQUIRE(result.z / result.w == Approx(-1));
    }

    SECTION("LookAt") {
        E::M::Vector3 eye(0, 0, 5);
        E::M::Vector3 target(0, 0, 0);
        E::M::Vector3 up(0, 1, 0);
        E::M::Matrix4 view = E::M::Matrix4::LookAt(eye, target, up);
        E::M::Vector4 eyePos(0, 0, 5, 1);
        E::M::Vector4 result = view * eyePos;
        REQUIRE(result.NearlyEquals(E::M::Vector4(0, 0, 0, 1)));

        E::M::Vector4 forwardWorld(0, 0, -1, 0);
        E::M::Vector4 viewForward = view * forwardWorld;
        REQUIRE(viewForward.NearlyEquals(E::M::Vector4(0, 0, -1, 0)));
    }
}
