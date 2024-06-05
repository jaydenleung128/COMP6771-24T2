#include "fib_vector.h"

#include <catch2/catch.hpp>

TEST_CASE("Works when n == 0")
{
    const auto expected = std::vector<int> {};
    auto nums = fibonacci(0);

    CHECK(nums == expected);
}

TEST_CASE("Works when n == 1")
{
    auto nums = fibonacci(1);

    CHECK(!nums.empty());
    CHECK(nums.size() == 1);

    CHECK(nums[0] == 1);
    CHECK(nums.at(0) == 1);
}

// add more tests here...