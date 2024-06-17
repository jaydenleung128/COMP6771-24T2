#include "invert.h"

#include <catch2/catch.hpp>

TEST_CASE("inversion of map with elements whose string keys collide inverts as expected") {
    auto data = std::map<std::string, int>{{"hi", 6771}, {"bob", 6771}};
    auto expected = std::map<int, std::string>{{6771, "bob"}};

    auto actual = invert(data);

    CHECK(actual == expected);
}

TEST_CASE("inversion of map with multiple disjoint elements inverts as expected") {
    auto data = std::map<std::string, int>{{"hi", 42}, {"bob", 6771}};
    auto expected = std::map<int, std::string>{{42, "hi"}, {6771, "bob"}};

    auto actual = invert(data);

    CHECK(actual == expected);
}

TEST_CASE("inversion of empty map is still empty") {
    auto data = std::map<std::string, int>{};
    auto expected = std::map<int, std::string>{};

    auto actual = invert(data);

    CHECK(actual == expected);
}

TEST_CASE("inversion of map with single element inverts as expected") {
    auto data = std::map<std::string, int>{{"hi", 42}};
    auto expected = std::map<int, std::string>{{42, "hi"}};

    auto actual = invert(data);

    CHECK(actual == expected);
}

TEST_CASE("spec example") {
    auto data = std::map<std::string, int>{
        {"a", 6771},
        {"ab", 6771},
        {"abc", 6771},
        {"xyz", 6772},
    };
    auto expected = std::map<int, std::string>{
        {6771, "abc"},
        {6772, "xyz"},
    };

    auto actual = invert(data);

    CHECK(actual == expected);
}
