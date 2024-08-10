#include "q1.h"
#include <catch2/catch.hpp>
#include <type_traits>


TEST_CASE("test") {
    double a = 1.0;

    CHECK(std::is_floating_point_v<decltype(a));
}

TEST_CASE("Simple add") {
    CHECK(q1::calculate({"1", "1", "add"}) == 2);
}

TEST_CASE("Simple sub") {
    CHECK(q1::calculate({"1", "1", "sub"}) == 0);
}

TEST_CASE("Simple mult") {
    CHECK(q1::calculate({"2", "2", "mult"}) == 4);
}

TEST_CASE("Simple div") {
    CHECK(q1::calculate({"2", "1", "div"}) == 2);
}

TEST_CASE("Simple sqrt") {
    CHECK(q1::calculate({ "4", "sqrt"}) == 2);
}

TEST_CASE("Simple pop add") {
    CHECK(q1::calculate({"1", "1", "1", "pop", "add"}) == 2);
}

TEST_CASE("Simple reverse sub") {
    CHECK(q1::calculate({"1", "2", "reverse", "sub"}) == 1);
}

// TEST_CASE("Simple repeat") {
//     CHECK(q1::run_calculator({
//         "1", 
//         "2", "repeat",
//             "1", "add", 
//         "endrepeat"}) == 3);
// }
