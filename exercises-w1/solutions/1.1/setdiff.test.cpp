#include "setdiff.h"

#include <catch2/catch.hpp>

/* These tests may not be exhaustive! */

TEST_CASE("Empty vector unchanged") {
    auto vs = std::vector<char>{};
    auto blacklist = std::vector<char>{'o', 'k'};

    const auto expected = std::vector<char>{};

    set_difference(vs, blacklist);

    CHECK(vs == expected);
}

TEST_CASE("Empty blacklist leaves vector unchanged") {
    auto vs = std::vector<char>{'6', '7', '7', '1'};
    auto blacklist = std::vector<char>{};

    const auto expected = std::vector<char>{'6', '7', '7', '1'};

    set_difference(vs, blacklist);

    CHECK(vs == expected);
}

TEST_CASE("Both empty does nothing", "Unneeded as both empty cases tested independently but here for demonstration") {
    auto vs = std::vector<char>{};
    auto blacklist = std::vector<char>{};

    const auto expected = std::vector<char>{};

    set_difference(vs, blacklist);

    CHECK(vs == expected);
}

TEST_CASE("Nothing happens if element is not present") {
    auto vs = std::vector<char>{'a', 'b'};
    auto blacklist = std::vector<char>{'c'};

    const auto expected = std::vector<char>{'a', 'b'};

    set_difference(vs, blacklist);

    CHECK(vs == expected);
}

TEST_CASE("Can successfully remove elements (multiple)") {
    auto vs = std::vector<char>{'a', 'b', 'a', 'd', 'b', 'd', 'c'};
    auto blacklist = std::vector<char>{'a', 'b'};

    const auto expected = std::vector<char>{'d', 'd', 'c'};

    set_difference(vs, blacklist);

    CHECK(vs == expected);
}

TEST_CASE("Can successfully remove elements (single)", "Unneeded as this is a special case of above but here for demonstration") {
    auto vs = std::vector<char>{'a', 'b'};
    auto blacklist = std::vector<char>{'a'};

    const auto expected = std::vector<char>{'b'};

    set_difference(vs, blacklist);

    CHECK(vs == expected);
}
