#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>

#include <cmath>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "Utilities/Math/Common/Comparison.hpp"
#include "Utilities/Math/Common/Constants.hpp"
#include "Utilities/Math/Common/Exponentials.hpp"
#include "Utilities/Math/Common/Logarithms.hpp"
#include "Utilities/Math/Common/Trigonometry.hpp"


using Catch::Approx;
using Catch::Matchers::WithinAbs;

TEST_CASE(


    "E::M::Rad"
) {
    REQUIRE(E::M::Rad(0.f) == Approx(0.f));
    REQUIRE(E::M::Rad(90.f) == Approx(E::M::PI / 2.f));
    REQUIRE(E::M::Rad(180.f) == Approx(E::M::PI));
    REQUIRE(E::M::Rad(360.f) == Approx(E::M::TAU));

    REQUIRE(E::M::Rad(-90.f) == Approx(-E::M::PI / 2.f));
    REQUIRE(E::M::Rad(-180.f) == Approx(-E::M::PI));
}

TEST_CASE(


    "E::M::Deg"
) {
    REQUIRE(E::M::Deg(0.f) == Approx(0.f));
    REQUIRE(E::M::Deg(E::M::PI / 2.f) == Approx(90.f));
    REQUIRE(E::M::Deg(E::M::PI) == Approx(180.f));
    REQUIRE(E::M::Deg(E::M::TAU) == Approx(360.f));

    REQUIRE(E::M::Deg(-E::M::PI / 2.f) == Approx(-90.f));
    REQUIRE(E::M::Deg(-E::M::PI) == Approx(-180.f));
}

TEST_CASE(


    "Degree/Radian round-trip"
) {
    for (float deg = -720.f; deg <= 720.f; deg += 15.f)
        REQUIRE(E::M::Deg(E::M::Rad(deg)) == Approx(deg));

    for (float rad = -10.f; rad <= 10.f; rad += 0.25f)
        REQUIRE(E::M::Rad(E::M::Deg(rad)) == Approx(rad));
}

TEST_CASE(


    "DSin matches std::sin"
) {
    REQUIRE(E::M::DSin(90.f) == Approx(1.f));
    REQUIRE(E::M::DSin(270.f) == Approx(-1.f));

    REQUIRE_THAT(E::M::DSin(0.f), WithinAbs(0.f, 1e-6f));
    REQUIRE_THAT(E::M::DSin(180.f), WithinAbs(0.f, 1e-6f));
    REQUIRE_THAT(E::M::DSin(360.f), WithinAbs(0.f, 1e-6f));

    for (float deg = -360.f; deg <= 360.f; deg += 1.f)
        REQUIRE(E::M::DSin(deg) == Approx(std::sin(E::M::Rad(deg))).margin(1e-6f));
}

TEST_CASE(


    "DCos matches std::cos"
) {
    REQUIRE(E::M::DCos(0.f) == Approx(1.f));
    REQUIRE(E::M::DCos(180.f) == Approx(-1.f));
    REQUIRE(E::M::DCos(360.f) == Approx(1.f));

    REQUIRE_THAT(E::M::DCos(90.f), WithinAbs(0.f, 1e-6f));
    REQUIRE_THAT(E::M::DCos(270.f), WithinAbs(0.f, 1e-6f));

    for (float deg = -360.f; deg <= 360.f; deg += 1.f)
        REQUIRE(E::M::DCos(deg) == Approx(std::cos(E::M::Rad(deg))).margin(1e-6f));
}

TEST_CASE(


    "DTan matches std::tan"
) {
    REQUIRE(E::M::DTan(45.f) == Approx(1.f));
    REQUIRE(E::M::DTan(-45.f) == Approx(-1.f));

    REQUIRE_THAT(E::M::DTan(0.f), WithinAbs(0.f, 1e-6f));
    REQUIRE_THAT(E::M::DTan(180.f), WithinAbs(0.f, 1e-6f));

    for (float deg = -360.f; deg <= 360.f; deg += 1.f) {
        float c = std::cos(E::M::Rad(deg));

        if (std::abs(c) > 1e-5f)
            REQUIRE(E::M::DTan(deg) == Approx(std::tan(E::M::Rad(deg))).margin(1e-5f));
    }
}

TEST_CASE(


    "Pow"
) {
    REQUIRE(E::M::Pow(2.f, 3.f) == Approx(8.f));
    REQUIRE(E::M::Pow(4.f, 0.5f) == Approx(2.f));
    REQUIRE(E::M::Pow(10.f, 0.f) == Approx(1.f));
    REQUIRE(E::M::Pow(2.f, -1.f) == Approx(0.5f));

    REQUIRE(E::M::Pow(-2.f, 2.f) == Approx(4.f));
    REQUIRE(E::M::Pow(-2.f, 3.f) == Approx(-8.f));

    for (float x = 0.1f; x <= 10.f; x += 0.25f)
        REQUIRE(E::M::Pow(x, 2.5f) == Approx(std::pow(x, 2.5f)));
}

TEST_CASE(


    "Sqrt"
) {
    REQUIRE(E::M::Sqrt(0.f) == Approx(0.f));
    REQUIRE(E::M::Sqrt(1.f) == Approx(1.f));
    REQUIRE(E::M::Sqrt(4.f) == Approx(2.f));
    REQUIRE(E::M::Sqrt(0.25f) == Approx(0.5f));
    REQUIRE(E::M::Sqrt(10000.f) == Approx(100.f));

    for (float x = 0.01f; x <= 100.f; x += 0.5f)
        REQUIRE(E::M::Sqrt(x) == Approx(std::sqrt(x)));
}

TEST_CASE(


    "Ln"
) {
    REQUIRE(E::M::Ln(1.f) == Approx(0.f));
    REQUIRE(E::M::Ln(E::M::E) == Approx(1.f));
    REQUIRE(E::M::Ln(E::M::E * E::M::E) == Approx(2.f));

    REQUIRE(std::isinf(E::M::Ln(0.f)));
    REQUIRE(std::isnan(E::M::Ln(-1.f)));

    for (float x = 0.1f; x <= 100.f; x += 0.25f)
        REQUIRE(E::M::Ln(x) == Approx(std::log(x)));
}

TEST_CASE(


    "Log"
) {
    REQUIRE(E::M::Log(10.f, 100.f) == Approx(2.f));
    REQUIRE(E::M::Log(2.f, 8.f) == Approx(3.f));
    REQUIRE(E::M::Log(5.f, 25.f) == Approx(2.f));
    REQUIRE(E::M::Log(E::M::E, 1.f) == Approx(0.f));

    REQUIRE(std::isinf(E::M::Log(1.f, 10.f)));
    REQUIRE(std::isnan(E::M::Log(-2.f, 8.f)));
    REQUIRE(std::isnan(E::M::Log(2.f, -8.f)));

    for (float base = 2.f; base <= 10.f; base += 1.f) {
        for (float x = 0.5f; x <= 100.f; x += 0.5f) {
            REQUIRE(E::M::Log(base, x) ==
                Approx(std::log(x) / std::log(base)));
        }
    }
}

TEST_CASE(


    "NearlyEquals"
) {
    constexpr float eps = E::M::EPSILON;

    REQUIRE(E::M::NearlyEquals(1.f, 1.f));
    REQUIRE(E::M::NearlyEquals(0.f, 0.f));
    REQUIRE(E::M::NearlyEquals(-5.f, -5.f));

    REQUIRE(E::M::NearlyEquals(1.f, 1.f + eps * 0.5f, eps));
    REQUIRE(E::M::NearlyEquals(1.f, 1.f - eps * 0.5f, eps));

    REQUIRE_FALSE(E::M::NearlyEquals(1.f, 1.f + eps * 2.f, eps));
    REQUIRE_FALSE(E::M::NearlyEquals(1.f, 1.f - eps * 2.f, eps));

    REQUIRE(E::M::NearlyEquals(1.f, 1.f, 0.f));
    REQUIRE_FALSE(E::M::NearlyEquals(1.f, 1.f + 1e-6f, 0.f));

    REQUIRE(E::M::NearlyEquals(0.f, 1e-6f, 1e-5f));
    REQUIRE_FALSE(E::M::NearlyEquals(0.f, 1e-4f, 1e-5f));
}
