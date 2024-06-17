#include "vsort.h"

#include <catch2/catch.hpp>

TEST_CASE("empty vector sortable") {
	std::vector<std::string> v = {};
	std::vector<std::string> exp = {};

	vsort(v);

	CHECK(v == exp);
}

TEST_CASE("when vowel count equal, sort lexicographically") {
	std::vector<std::string> v = {"heey", "there", "world"};
	std::vector<std::string> exp = {"world", "heey", "there"};

	vsort(v);

	CHECK(v == exp);
}

TEST_CASE("already in-order doesn't change order") {
	std::vector<std::string> v = {"hi", "worldo"};
	std::vector<std::string> exp = {"hi", "worldo"};

	vsort(v);

	CHECK(v == exp);
}

TEST_CASE("not in order -> sorted in order") {
	std::vector<std::string> v = {"heeey", "there", "world"};
	std::vector<std::string> exp = {"world", "there", "heeey"};

	vsort(v);

	CHECK(v == exp);
}
