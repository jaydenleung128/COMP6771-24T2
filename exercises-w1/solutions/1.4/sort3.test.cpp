#include "sort3.h"
#include <catch2/catch.hpp>

TEST_CASE("int: All same object") {
    int x = 0;
    
    sort3(x, x, x);
    
    CHECK(x == 0);
}

TEST_CASE("int: Pre-sorted") {
    int x = 0;
    int y = 1;
    int z = 2;
    
    sort3(x, y, z);
    
    CHECK(x < y);
    CHECK(y < z);
}

TEST_CASE("int: Descending") {
    int x = 0;
    int y = 1;
    int z = 2;

    sort3(z, y, x);
    
    CHECK(z < y);
    CHECK(y < x);
}

TEST_CASE("int: Two same, one different") {
    int x = 0;
    int y = 1;
    int z = 2;

    x = y;
    sort3(x, z, y);
    CHECK(x == z);
    CHECK(x < y);

    sort3(y, x, z);
    CHECK(x == y);
    CHECK(x < z);
}

TEST_CASE("str: All same object") {
	auto x = std::string("hello");
	auto y = std::string("there");
	auto z = std::string("world");

    sort3(x, x, x);
    CHECK(x == "hello");
}

TEST_CASE("str: Pre-sorted") {
	auto x = std::string("hello");
	auto y = std::string("there");
	auto z = std::string("world");

    sort3(x, y, z);
    CHECK(x < y);
    CHECK(y < z);
}

TEST_CASE("str: Descending") {
	auto x = std::string("hello");
	auto y = std::string("there");
	auto z = std::string("world");

    sort3(z, y, x);
    CHECK(z < y);
    CHECK(y < x);
}

TEST_CASE("str: Two same, one different") {
	auto x = std::string("hello");
	auto y = std::string("there");
	auto z = std::string("world");

    x = y;
    sort3(x, z, y);
    CHECK(x == z);
    CHECK(x < y);

    sort3(y, x, z);
    CHECK(x == y);
    CHECK(x < z);
}
