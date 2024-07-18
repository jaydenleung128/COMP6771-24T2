#include "rational.h"

#include <catch2/catch.hpp>

#include <type_traits>

TEST_CASE("Rational number is const-correct") {
    CHECK(std::is_invocable_v<decltype(&rational_number::value), const rational_number>);
}

TEST_CASE("rational number constructible with defined value") {
    auto rat = rational_number::make_rational(2, 5);
    const auto expected = 0.4;

    CHECK(rat->value() == expected);
}

TEST_CASE("rational number constructible with defined value") {
    auto rat = rational_number::make_rational(2, 0);

    CHECK(!rat);
}

TEST_CASE("Rational number is const-correct") {
    auto rat = rational_number::make_rational(2, 5);
    const auto expected = 0.4;

    CHECK(rat->value() == expected);
}

TEST_CASE("Can add two rational numbers") {
    auto r1 = *rational_number::make_rational(1, 2);
    auto r2 = *rational_number::make_rational(3, 5);

    const auto expected = *rational_number::make_rational(11, 10);

    auto r = add(r1, r2);
    
    CHECK(eq(r, expected));
}

TEST_CASE("Can divide two rational numbers") {
    auto r1 = *rational_number::make_rational(1, 2);
    auto r2 = *rational_number::make_rational(3, 5);

    const auto expected = *rational_number::make_rational(5, 6);

    auto r = *div(r1, r2);

    CHECK(eq(r, expected));
}

TEST_CASE("Rational number is equality comparable") {
    CHECK(eq(*rational_number::make_rational(1, 2), *rational_number::make_rational(2, 4)));
}

TEST_CASE("Can multiply two rational numbers") {
    auto r1 = *rational_number::make_rational(1, 2);
    auto r2 = *rational_number::make_rational(3, 5);

    const auto expected = *rational_number::make_rational(3, 10);

    auto r = mul(r1, r2);

    CHECK(eq(r, expected));
}

TEST_CASE("Rational number is inequality comparable") {
    CHECK(ne(*rational_number::make_rational(1, 2), *rational_number::make_rational(3, 4)));
}

TEST_CASE("Can subtract two rational numbers") {
    auto r1 = *rational_number::make_rational(1, 2);
    auto r2 = *rational_number::make_rational(3, 5);

    const auto expected = *rational_number::make_rational(-1, 10);

    auto r = sub(r1, r2);

    CHECK(eq(r, expected));
}

TEST_CASE("Rational number size requirement met") {
    CHECK(sizeof(rational_number) <= 16);
}

TEST_CASE("Rational number has public static data member") {
    CHECK(!rational_number::null.has_value());
}
