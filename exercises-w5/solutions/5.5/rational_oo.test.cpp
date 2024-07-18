#include "rational_oo.h"

#include <catch2/catch.hpp>

#include <type_traits>

TEST_CASE("Rational number is const-correct") {
    CHECK(std::is_invocable_v<decltype(&rational_number::operator double), const rational_number>);

    auto(rational_number::*pf)(char) const = &rational_number::operator[];
    CHECK(std::is_invocable_v<decltype(pf), const rational_number, char>);
}

TEST_CASE("rational number constructible with defined value") {
    auto rat = *rational_number::make_rational(2, 5);
    const auto expected = 0.4;

    CHECK(static_cast<double>(rat) == expected);
}


TEST_CASE("rational number constructible with defined value") {
    auto rat = rational_number::make_rational(2, 0);

    CHECK(!rat);
}

TEST_CASE("Can add two rational numbers") {
    auto r1 = *rational_number::make_rational(1, 2);
    auto r2 = *rational_number::make_rational(3, 5);

    const auto expected = *rational_number::make_rational(11, 10);

    auto r = r1 + r2;
    
    CHECK(r == expected);
}

TEST_CASE("Can divide two rational numbers") {
    auto r1 = *rational_number::make_rational(1, 2);
    auto r2 = *rational_number::make_rational(3, 5);

    const auto expected = *rational_number::make_rational(5, 6);

    auto r = *(r1 / r2);

    CHECK(r == expected);
}

TEST_CASE("Rational number is equality comparable") {
    CHECK(rational_number::make_rational(1, 2) == rational_number::make_rational(2, 4));
}

TEST_CASE("Rational number is const-correct") {
    auto rat = *rational_number::make_rational(2, 5);
    const auto expected = 0.4;

    CHECK(static_cast<double>(rat) == expected);
}

TEST_CASE("Can multiply two rational numbers") {
    auto r1 = *rational_number::make_rational(1, 2);
    auto r2 = *rational_number::make_rational(3, 5);

    const auto expected = *rational_number::make_rational(3, 10);

    auto r = r1 * r2;

    CHECK(r == expected);
}

TEST_CASE("Rational number is inequality comparable") {
    CHECK(rational_number::make_rational(1, 2) != rational_number::make_rational(3, 4));
}


TEST_CASE("Can subtract two rational numbers") {
    auto r1 = *rational_number::make_rational(1, 2);
    auto r2 = *rational_number::make_rational(3, 5);

    const auto expected = *rational_number::make_rational(-1, 10);

    auto r = r1 - r2;

    CHECK(r == expected);
}


TEST_CASE("Rational number denominator accessible") {
    auto rat = *rational_number::make_rational(2, 1);
    SECTION("as getter") {
        CHECK(rat['v'] == 1);
    }

    SECTION("as setter") {
        rat['v'] = 2;

        const auto expected = *rational_number::make_rational(2, 2);

        CHECK(rat == expected);
    }
}


TEST_CASE("Rational number numerator accessible") {
    auto rat = *rational_number::make_rational(1, 2);
    SECTION("as getter") {
        CHECK(rat['^'] == 1);
    }

    SECTION("as setter") {
        rat['^'] = 2;

        const auto expected = *rational_number::make_rational(2, 2);

        CHECK(rat == expected);
    }
}


TEST_CASE("Rational number size requirement met") {
    CHECK(sizeof(rational_number) <= 16);
}


TEST_CASE("Rational number has public static data member") {
    CHECK(!rational_number::null.has_value());
}
