#include "vec3.h"

#include <catch2/catch.hpp>

#include <type_traits>

TEST_CASE("vec3 is copyable") {
    CHECK((std::is_copy_constructible_v<vec3> && std::is_copy_assignable_v<vec3>));
}

TEST_CASE("vec3 is default constructible") {
    vec3 v = {};

    CHECK((v.x == 0 && v.y == 0 && v.z == 0));
}

TEST_CASE("vec3 is constructible with 3 arguments") {
    vec3 v = {1, 2, 3};

    CHECK((v.x == 1 && v.y == 2 && v.z == 3));
}

TEST_CASE("vec3 is constructible with a single argument") {
    vec3 v = vec3{1};

    CHECK((v.x == 1 && v.y == 1 && v.z == 1));
}

TEST_CASE("vec3 is destructible") {
    CHECK(std::is_destructible_v<vec3>);
}


TEST_CASE("vec3's single arg constructor is explicit") {
    CHECK(!std::is_convertible_v<int, vec3>);
}

TEST_CASE("vec3 has r, g, b distinct members") {
    vec3 v = {0.25, 0.5, 0.75};

    CHECK((v.r == 0.25 && v.g == 0.5 && v.b == 0.75));
}

TEST_CASE("vec3 has x, y, z distinct members") {
    vec3 v = {1, -1, 0};

    CHECK((v.x == 1 && v.y == -1 && v.z == 0));
}

TEST_CASE("vec3 has s, t, p distinct members") {
    vec3 v = {0.75, -0.75, 0.5};

    CHECK((v.s == 0.75 && v.t == -0.75 && v.p == 0.5));
}

TEST_CASE("vec3 is sizeof(double) * 3") {
    CHECK(sizeof(vec3) == sizeof(double) * 3);
}
