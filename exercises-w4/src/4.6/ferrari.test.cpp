#include "./ferrari.h"

#include <catch2/catch.hpp>
#include <string>
#include <utility>

TEST_CASE("default construct0r") {
    const auto a = ferrari{};
    CHECK(a.get_details() == std::make_pair(std::string("unknown"), 6771)); 
}



