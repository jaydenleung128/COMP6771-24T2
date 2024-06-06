#include "permutation.h"

#include <catch2/catch.hpp>

TEST_CASE("empty string permutation of itself") {
    std::string s1 = "";
    std::string s2 = "";
    
    CHECK(is_permutation(s1, s2));
}

TEST_CASE("identical strings are permutations") {
    std::string s1 = "abc";
    std::string s2 = "abc";
    
    CHECK(is_permutation(s1, s2));
}

TEST_CASE("strings of different length are not permutations") {
    std::string s1 = "abc";
    std::string s2 = "ab";
    
    CHECK(!is_permutation(s1, s2));
}

TEST_CASE("an actual permutation") {
    std::string s1 = "abc";
    std::string s2 = "cba";
    
    CHECK(is_permutation(s1, s2));
}
