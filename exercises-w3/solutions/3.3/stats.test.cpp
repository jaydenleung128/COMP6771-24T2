#include "stats.h"

#include <catch2/catch.hpp>

TEST_CASE("can load the basic marks file") {
    auto expected = std::vector<int> {
        2,
        14,
        90,
        56,
        88,
        44,
        76,
        33,
        100,
        4,
        47,
        67,
        71,
        8
    };

    CHECK(read_marks("../src/3.3/marks.txt") == expected);
}

bool operator==(const stats &s1, const stats &s2) {
    return s1.avg == s2.avg &&
           s1.median == s2.median &&
           s1.highest == s2.highest &&
           s1.lowest == s2.lowest;
}

TEST_CASE("correct stats for marking.txt") {
    auto statistics = std::vector<int> {
        2,
        14,
        90,
        56,
        88,
    };

    auto expected = stats{
        .avg = 50,
        .median = 56,
        .highest = 90,
        .lowest = 2
    };

    auto actual = calculate_stats(statistics);

    CHECK(actual == expected);
}

TEST_CASE("correct stats for assorted.txt") {
    auto statistics = std::vector<int> {0, -1, 11, -2, 22};

    auto expected = stats{
        .avg = 6,
        .median = 0,
        .highest = 22,
        .lowest = -2
    };

    auto actual = calculate_stats(statistics);

    CHECK(actual == expected);
}
