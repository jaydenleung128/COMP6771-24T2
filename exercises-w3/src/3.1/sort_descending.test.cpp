#include "./sort_descending.h"
#include <catch2/catch.hpp>

TEST_CASE("Sort")
{
    auto v = std::vector<int>{1,2,3};
    sort_descending(v);
    CHECK(v == std::vector<int>{3,2,1});
}
