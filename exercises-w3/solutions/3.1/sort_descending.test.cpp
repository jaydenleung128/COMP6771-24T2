#include "sort_descending.h"
#include <catch2/catch.hpp>

TEST_CASE("empty vector") {
    auto v = std::vector<int>();

    sort_descending(v);

    CHECK(std::is_sorted(v.begin(), v.end(), std::greater{}));
}

TEST_CASE("many elements") {
    auto v = std::vector<int>{36, 84, 122, 76, 41, 19};

    sort_descending(v);

    CHECK(std::is_sorted(v.begin(), v.end(), std::greater{}));

}

TEST_CASE("single-element vector") {
    auto v = std::vector<int>{1};

    sort_descending(v);

    CHECK(std::is_sorted(v.begin(), v.end(), std::greater{}));
}
