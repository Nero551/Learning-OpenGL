#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>

#include <cmath>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "Utilities/Math/MathUtils.hpp"

using Catch::Approx;
using Catch::Matchers::WithinAbs;

TEST_CASE (


"Math::Rad"
)
 {
    REQUIRE(Math::Rad(0.f) == Approx(0.f));
    REQUIRE(Math::Rad(90.f) == Approx(Math::PI / 2.f));
    REQUIRE(Math::Rad(180.f) == Approx(Math::PI));
    REQUIRE(Math::Rad(360.f) == Approx(Math::TAU));

    REQUIRE(Math::Rad(-90.f) == Approx(-Math::PI / 2.f));
    REQUIRE(Math::Rad(-180.f) == Approx(-Math::PI));
}

TEST_CASE (


"Math::Deg"
)
 {
    REQUIRE(Math::Deg(0.f) == Approx(0.f));
    REQUIRE(Math::Deg(Math::PI / 2.f) == Approx(90.f));
    REQUIRE(Math::Deg(Math::PI) == Approx(180.f));
    REQUIRE(Math::Deg(Math::TAU) == Approx(360.f));

    REQUIRE(Math::Deg(-Math::PI / 2.f) == Approx(-90.f));
    REQUIRE(Math::Deg(-Math::PI) == Approx(-180.f));
}

TEST_CASE (


"Degree/Radian round-trip"
)
 {
    for (float deg = -720.f; deg <= 720.f; deg += 15.f)
        REQUIRE(Math::Deg(Math::Rad(deg)) == Approx(deg));

    for (float rad = -10.f; rad <= 10.f; rad += 0.25f)
        REQUIRE(Math::Rad(Math::Deg(rad)) == Approx(rad));
}

TEST_CASE (


"DSin matches std::sin"
)
 {
    REQUIRE(Math::DSin(90.f) == Approx(1.f));
    REQUIRE(Math::DSin(270.f) == Approx(-1.f));

    REQUIRE_THAT(Math::DSin(0.f), WithinAbs(0.f, 1e-6f));
    REQUIRE_THAT(Math::DSin(180.f), WithinAbs(0.f, 1e-6f));
    REQUIRE_THAT(Math::DSin(360.f), WithinAbs(0.f, 1e-6f));

    for (float deg = -360.f; deg <= 360.f; deg += 1.f)
        REQUIRE(Math::DSin(deg) == Approx(std::sin(Math::Rad(deg))).margin(1e-6f));
}

TEST_CASE (


"DCos matches std::cos"
)
 {
    REQUIRE(Math::DCos(0.f) == Approx(1.f));
    REQUIRE(Math::DCos(180.f) == Approx(-1.f));
    REQUIRE(Math::DCos(360.f) == Approx(1.f));

    REQUIRE_THAT(Math::DCos(90.f), WithinAbs(0.f, 1e-6f));
    REQUIRE_THAT(Math::DCos(270.f), WithinAbs(0.f, 1e-6f));

    for (float deg = -360.f; deg <= 360.f; deg += 1.f)
        REQUIRE(Math::DCos(deg) == Approx(std::cos(Math::Rad(deg))).margin(1e-6f));
}

TEST_CASE (


"DTan matches std::tan"
)
 {
    REQUIRE(Math::DTan(45.f) == Approx(1.f));
    REQUIRE(Math::DTan(-45.f) == Approx(-1.f));

    REQUIRE_THAT(Math::DTan(0.f), WithinAbs(0.f, 1e-6f));
    REQUIRE_THAT(Math::DTan(180.f), WithinAbs(0.f, 1e-6f));

    for (float deg = -360.f; deg <= 360.f; deg += 1.f) {
        float c = std::cos(Math::Rad(deg));

        if (std::abs(c) > 1e-5f)
            REQUIRE(Math::DTan(deg) == Approx(std::tan(Math::Rad(deg))).margin(1e-5f));
    }
}

TEST_CASE (


"Pow"
)
 {
    REQUIRE(Math::Pow(2.f, 3.f) == Approx(8.f));
    REQUIRE(Math::Pow(4.f, 0.5f) == Approx(2.f));
    REQUIRE(Math::Pow(10.f, 0.f) == Approx(1.f));
    REQUIRE(Math::Pow(2.f, -1.f) == Approx(0.5f));

    REQUIRE(Math::Pow(-2.f, 2.f) == Approx(4.f));
    REQUIRE(Math::Pow(-2.f, 3.f) == Approx(-8.f));

    for (float x = 0.1f; x <= 10.f; x += 0.25f)
        REQUIRE(Math::Pow(x, 2.5f) == Approx(std::pow(x, 2.5f)));
}

TEST_CASE (


"Sqrt"
)
 {
    REQUIRE(Math::Sqrt(0.f) == Approx(0.f));
    REQUIRE(Math::Sqrt(1.f) == Approx(1.f));
    REQUIRE(Math::Sqrt(4.f) == Approx(2.f));
    REQUIRE(Math::Sqrt(0.25f) == Approx(0.5f));
    REQUIRE(Math::Sqrt(10000.f) == Approx(100.f));

    for (float x = 0.01f; x <= 100.f; x += 0.5f)
        REQUIRE(Math::Sqrt(x) == Approx(std::sqrt(x)));
}

TEST_CASE (


"Ln"
)
 {
    REQUIRE(Math::Ln(1.f) == Approx(0.f));
    REQUIRE(Math::Ln(Math::E) == Approx(1.f));
    REQUIRE(Math::Ln(Math::E * Math::E) == Approx(2.f));

    REQUIRE(std::isinf(Math::Ln(0.f)));
    REQUIRE(std::isnan(Math::Ln(-1.f)));

    for (float x = 0.1f; x <= 100.f; x += 0.25f)
        REQUIRE(Math::Ln(x) == Approx(std::log(x)));
}

TEST_CASE (


"Log"
)
 {
    REQUIRE(Math::Log(10.f, 100.f) == Approx(2.f));
    REQUIRE(Math::Log(2.f, 8.f) == Approx(3.f));
    REQUIRE(Math::Log(5.f, 25.f) == Approx(2.f));
    REQUIRE(Math::Log(Math::E, 1.f) == Approx(0.f));

    REQUIRE(std::isinf(Math::Log(1.f, 10.f)));
    REQUIRE(std::isnan(Math::Log(-2.f, 8.f)));
    REQUIRE(std::isnan(Math::Log(2.f, -8.f)));

    for (float base = 2.f; base <= 10.f; base += 1.f) {
        for (float x = 0.5f; x <= 100.f; x += 0.5f) {
            REQUIRE(Math::Log(base, x) ==
                Approx(std::log(x) / std::log(base)));
        }
    }
}

TEST_CASE (


"NearlyEquals"
)
 {
    constexpr float eps = Math::EPSILON;

    REQUIRE(Math::NearlyEquals(1.f, 1.f));
    REQUIRE(Math::NearlyEquals(0.f, 0.f));
    REQUIRE(Math::NearlyEquals(-5.f, -5.f));

    REQUIRE(Math::NearlyEquals(1.f, 1.f + eps * 0.5f, eps));
    REQUIRE(Math::NearlyEquals(1.f, 1.f - eps * 0.5f, eps));

    REQUIRE_FALSE(Math::NearlyEquals(1.f, 1.f + eps * 2.f, eps));
    REQUIRE_FALSE(Math::NearlyEquals(1.f, 1.f - eps * 2.f, eps));

    REQUIRE(Math::NearlyEquals(1.f, 1.f, 0.f));
    REQUIRE_FALSE(Math::NearlyEquals(1.f, 1.f + 1e-6f, 0.f));

    REQUIRE(Math::NearlyEquals(0.f, 1e-6f, 1e-5f));
    REQUIRE_FALSE(Math::NearlyEquals(0.f, 1e-4f, 1e-5f));
}
