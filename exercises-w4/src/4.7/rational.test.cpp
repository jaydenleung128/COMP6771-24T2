#include "rational.h"

#include <catch2/catch.hpp>

TEST_CASE("failure is not an option") {
    constexpr auto failure_is_not_an_option = []{ return false; };
    REQUIRE(failure_is_not_an_option());
}
