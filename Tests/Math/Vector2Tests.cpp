#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include "Utilities/Math/Vector/Vector2.hpp"
#include <cmath>
#include <catch2/catch_approx.hpp>

using Catch::Matchers::WithinRel;
using Catch::Matchers::WithinAbs;
using Catch::Approx;

TEST_CASE("Vector2 construction and constants") {
    Vector2 v(1.0f, 2.0f);
    REQUIRE(v.x == 1.0f);
    REQUIRE(v.y == 2.0f);

    Vector2 all(5.0f);
    REQUIRE(all == Vector2(5.0f, 5.0f));

    REQUIRE(Vector2::Zero == Vector2(0.0f, 0.0f));
}

TEST_CASE("Vector2 arithmetic") {
    Vector2 a(1.0f, 2.0f);
    Vector2 b(4.0f, 6.0f);

    SECTION("vector addition") {
        REQUIRE(a + b == Vector2(5.0f, 8.0f));
        a += b;
        REQUIRE(a == Vector2(5.0f, 8.0f));
    }

    SECTION("vector subtraction") {
        REQUIRE(b - a == Vector2(3.0f, 4.0f));
        b -= a;
        REQUIRE(b == Vector2(3.0f, 4.0f));
    }

    SECTION("component‑wise multiplication") {
        REQUIRE(a * b == Vector2(4.0f, 12.0f));
        a *= b;
        REQUIRE(a == Vector2(4.0f, 12.0f));
    }

    SECTION("scalar operations") {
        REQUIRE(a + 3.0f == Vector2(4.0f, 5.0f));
        REQUIRE(a - 1.0f == Vector2(0.0f, 1.0f));
        REQUIRE(a * 2.0f == Vector2(2.0f, 4.0f));
        REQUIRE(a / 2.0f == Vector2(0.5f, 1.0f));
        REQUIRE(3.0f + a == Vector2(4.0f, 5.0f));
        REQUIRE(3.0f - a == Vector2(2.0f, 1.0f));
        REQUIRE(3.0f * a == Vector2(3.0f, 6.0f));
        REQUIRE(3.0f / a == Vector2(3.0f, 1.5f));
    }

    SECTION("unary negation") {
        REQUIRE(-a == Vector2(-1.0f, -2.0f));
    }

    SECTION("equality") {
        REQUIRE(a == Vector2(1.0f, 2.0f));
        REQUIRE(a != Vector2(2.0f, 2.0f));
    }
}

TEST_CASE("Vector2 methods") {
    Vector2 a(3.0f, 4.0f);
    Vector2 b(1.0f, 2.0f);

    SECTION("length and length squared") {
        REQUIRE(a.LengthSquared() == 25.0f);
        REQUIRE(a.Length() == 5.0f);
        REQUIRE(b.LengthSquared() == 5.0f);
        REQUIRE(b.Length() == Approx(std::sqrt(5.0f)));
    }

    SECTION("dot product") {
        REQUIRE(a.Dot(b) == 3.0f * 1.0f + 4.0f * 2.0f);
        REQUIRE(b.Dot(a) == a.Dot(b));
    }

    SECTION("distance") {
        REQUIRE(a.Distance(b) == Approx(std::sqrt(8.0f)));
    }

    SECTION("normalization") {
        Vector2 n = a.Normalized();
        REQUIRE(n.Length() == Approx(1.0f));
        REQUIRE(n == Vector2(0.6f, 0.8f));

        Vector2 zero = Vector2::Zero;
        REQUIRE(zero.Normalized() == Vector2::Zero);
    }

    SECTION("nearly equals") {
        Vector2 a2(1.000001f, 2.000001f);
        REQUIRE(a2.NearlyEquals(a) == true);
        Vector2 a3(1.0001f, 2.0f);
        REQUIRE(a3.NearlyEquals(a) == false);
    }
}