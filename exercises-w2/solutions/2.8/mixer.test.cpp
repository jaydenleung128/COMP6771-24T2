#include "mixer.h"

#include <catch2/catch.hpp>

std::optional<paint> identity(paint p1, paint p2) {
    if (p1 == p2) {
        return std::optional<paint>{p1};
    } else {
        return std::optional<paint>{};
    }
}

TEST_CASE("custom mixing strats") {
    CHECK(mix({paint::RED, paint::RED}, identity).value() == paint::RED);
}

TEST_CASE("cannot mix more than 2 paints together with an invalid combination") {
    CHECK(!mix({paint::RED, paint::BROWN, paint::YELLOW}).has_value());
}

TEST_CASE("can mix more than 2 paints together with a valid combination") {
    CHECK(*mix({paint::RED, paint::GREEN, paint::CYAN}) == paint::BROWN);
}

TEST_CASE("cannot mix 2 paints together with an invalid combination") {
    CHECK(!mix({paint::RED, paint::BROWN}).has_value());
} 

TEST_CASE("can mix 2 paints together with a valid combination") {
    CHECK(*mix({paint::RED, paint::BLUE}) == paint::MAGENTA);
}  

TEST_CASE("paint is an enum class with sizeof(underlying_type) == 1. char/unsigned char") {
    CHECK(sizeof(paint::RED) == 1);
}

TEST_CASE("brown + brown == brown") {
    paint c1 = paint::BROWN;
    paint c2 = paint::BROWN;
    paint c3 = paint::BROWN;

    CHECK(*wacky_colour(c1, c2) == c3);
}

TEST_CASE("cyan + magenta == brown") {
    paint c1 = paint::CYAN;
    paint c2 = paint::MAGENTA;
    paint c3 = paint::BROWN;

    CHECK(*wacky_colour(c1, c2) == c3);
}

TEST_CASE("green + blue == cyan") {
    paint c1 = paint::GREEN;
    paint c2 = paint::BLUE;
    paint c3 = paint::CYAN;

    CHECK(*wacky_colour(c1, c2) == c3);
}

TEST_CASE("brown + cyan == ") {
    paint c1 = paint::BROWN;
    paint c2 = paint::CYAN;

    CHECK(!wacky_colour(c1, c2).has_value());
}

TEST_CASE("red + blue == magenta") {
    paint c1 = paint::RED;
    paint c2 = paint::BLUE;
    paint c3 = paint::MAGENTA;

    CHECK(*wacky_colour(c1, c2) == c3);
}

TEST_CASE("red + green == yellow") {
    paint c1 = paint::RED;
    paint c2 = paint::GREEN;
    paint c3 = paint::YELLOW;

    CHECK(*wacky_colour(c1, c2) == c3);
}

TEST_CASE("yellow + cyan == brown") {
    paint c1 = paint::YELLOW;
    paint c2 = paint::CYAN;
    paint c3 = paint::BROWN;

    CHECK(*wacky_colour(c1, c2) == c3);
}

TEST_CASE("yellow + magenta == brown") {
    paint c1 = paint::YELLOW;
    paint c2 = paint::MAGENTA;
    paint c3 = paint::BROWN;

    CHECK(*wacky_colour(c1, c2) == c3);
}
