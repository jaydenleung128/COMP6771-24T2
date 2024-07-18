#include "book.h"

#include <catch2/catch.hpp>

#include <type_traits>
#include <sstream>

TEST_CASE("book is const-correct") {
    CHECK(std::is_invocable_r_v<std::string, decltype(&book::operator std::string), const book>);
    CHECK(std::is_invocable_r_v<std::string, decltype(&book::name), const book>);
    CHECK(std::is_invocable_r_v<std::string, decltype(&book::author), const book>);
    CHECK(std::is_invocable_r_v<std::string, decltype(&book::isbn), const book>);
    CHECK(std::is_invocable_r_v<double, decltype(&book::price), const book>);
}

TEST_CASE("book is constructible according to the spec") {
    book b = {"swag", "streets", "something", 0.25};

    CHECK(b.name() == "swag");
    CHECK(b.author() == "streets");
    CHECK(b.isbn() == "something");
    CHECK(b.price() == 0.25);
}

TEST_CASE("Can get the author of a book") {
    book b = {"", "cse", "", 0};

    CHECK(b.author() == "cse");
}

TEST_CASE("Can get the ISBN of a book") {
    book b = {"", "", "0123456789X", 0};

    CHECK(b.isbn() == "0123456789X");
}

TEST_CASE("Can get the name of a book") {
    book b = {"how to attain dreams", "", "", 0};

    CHECK(b.name() == "how to attain dreams");
}


TEST_CASE("Can get the price of a book") {
    book b = {"", "", "", -0.5};

    CHECK(b.price() == -0.5);
}

TEST_CASE("Two books compare equal") {
    book b1 = {"sleep smarter", "shawn stevenson", "I don't know", 50};
    book b2 = {"sleep smarter", "shawn stevenson", "I don't know", 50};

    CHECK(b1 == b2);
}

TEST_CASE("Two books are sorted based on ISBN") {
    book b1 = {"a", "b", "apples", 0};
    book b2 = {"a", "b", "banana", 0};

    REQUIRE(!(b1 == b2));
    REQUIRE(!(b2 < b1));
    CHECK(b1 < b2);
}

TEST_CASE("Two books compare inequal") {
    book b1 = {"sleep smarter", "shawn stevenson", "I don't know", 50};
    book b2 = {"sleep dumber", "stawn shevenson", "I _do_ know", 51};

    CHECK(b1 != b2);
}

TEST_CASE("book printed according to spec") {
    SECTION("when rounding has no effect") {
        book b = {"a", "b", "c", 50};
        const std::string expected = "a, b, c, $50.00";

        std::ostringstream bs{};
        bs << b;

        CHECK(bs.str() == expected);
    }

    SECTION("when rounding price has an effect") {
        SECTION("round toward 0") {
            book b = {"a", "b", "c", 17.233};
            const std::string expected = "a, b, c, $17.23";

            std::ostringstream bs;
            bs << b;

            CHECK(bs.str() == expected);
        }

        SECTION("round away from 0") {
            book b = {"a", "b", "c", 12.396};
            const std::string expected = "a, b, c, $12.40";

            std::ostringstream bs;
            bs << b;

            CHECK(bs.str() == expected);
        }
    }
}

TEST_CASE("book is convertible to a std::string according to the spec") {
    book b = {"Tour of C++11", "Bjarne Stroustrup", "0123456789X", 9000};
    const std::string expected = "Bjarne Stroustrup, Tour of C++11";
    
    std::string s = static_cast<std::string>(b);

    CHECK(s == expected);
}

