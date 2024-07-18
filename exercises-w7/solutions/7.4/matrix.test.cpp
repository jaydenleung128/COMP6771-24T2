#include "matrix.h"

#include <catch2/catch.hpp>
#include <type_traits>

TEST_CASE("Can nothrow copy-construct a matrix") {
    CHECK(!std::is_nothrow_copy_constructible_v<matrix>);
}


TEST_CASE("Can copy construct a matrix") {
    auto m1 = matrix{
        {1, 1, 1},
        {1, 1, 1},
        {1, 1, 1}
    };

    auto m2 = m1;
    CHECK(m1 == m2);
    
    SECTION("actually deep-copied") {
        m1(0, 0) = 4;

        CHECK(m2(0, 0) == 1);
    }
}


TEST_CASE("Can default construct a matrix") {
    auto m = matrix{};

    CHECK(m.dimensions() == std::make_pair<std::size_t, std::size_t>(0, 0));
    CHECK(m.data() == nullptr);
}

TEST_CASE("Cannot contruct a matrix with an invalid initialiser list") {
    using Catch::Message;

    CHECK_THROWS_MATCHES(matrix({{1}, {1, 1}}), std::logic_error, Message("Columns are not equal length"));
}


TEST_CASE("Can contruct a matrix with a valid initialiser list") {
    auto m = matrix{
        {1, 1, 1},
        {1, 1, 1},
        {1, 1, 1}
    };

    const auto &[r, c] = m.dimensions();

    REQUIRE((r == c && r == 3));

    for (auto i = 0u; i < r; ++i) {
        for (auto j = 0u; j < c; ++j) {
            REQUIRE(m(i, j) == 1);
        }
    }
    
}


TEST_CASE("Can nothrow move-construct a matrix") {
    CHECK(std::is_nothrow_move_constructible_v<matrix>);
}


TEST_CASE("Can move construct a matrix") {
    auto m1 = matrix{
        {1, 1, 1},
        {1, 1, 1},
        {1, 1, 1}
    };

    auto m2 = std::move(m1);

    CHECK(m1.dimensions() == std::make_pair<std::size_t, std::size_t>(0, 0));
    CHECK(m1.data_ == nullptr);

    const auto &[r, c] = m2.dimensions();
    REQUIRE((r == c && r == 3));

    for (auto i = 0u; i < r; ++i) {
        for (auto j = 0u; j < c; ++j) {
            REQUIRE(m2(i, j) == 1);
        }
    }
}


TEST_CASE("Can get a pointer to the underlying data (const)") {
    const auto m = matrix{
        {1, 1, 1},
        {1, 1, 1},
        {1, 1, 1}
    };

    constexpr int ints[9] = {1, 1, 1, 1, 1, 1, 1, 1, 1};
    CHECK(std::equal(m.data(), m.data() + 9, ints));
}


TEST_CASE("Can get a pointer to the underlying data (const)") {
    const auto m = matrix{
        {1, 1, 1},
        {1, 1, 1},
        {1, 1, 1}
    };

    constexpr int ints[9] = {1, 1, 1, 1, 1, 1, 1, 1, 1};
    CHECK(std::equal(m.data(), m.data() + 9, ints));
}

TEST_CASE("Can get a pointer to the underlying data") {
    auto m = matrix{
        {1, 1, 1},
        {1, 1, 1},
        {1, 1, 1}
    };

    constexpr int ints[9] = {1, 1, 1, 1, 1, 1, 1, 1, 1};
    CHECK(std::equal(m.data(), m.data() + 9, ints));
}

TEST_CASE("Can get dimensions of a matrix (const-correct)") {
    const auto m = matrix{
        {1, 1, 1},
        {1, 1, 1},
        {1, 1, 1}
    };

    CHECK(m.dimensions() == std::make_pair<std::size_t, std::size_t>(3, 3));
}

TEST_CASE("Can get dimensions of a matrix") {
    auto m = matrix{
        {1, 1, 1},
        {1, 1, 1},
        {1, 1, 1}
    };

    CHECK(m.dimensions() == std::make_pair<std::size_t, std::size_t>(3, 3));
}


TEST_CASE(".get() throws for invalid indices") {
    const auto m = matrix{};

    using Catch::Message;
    CHECK_THROWS_MATCHES(m(1, 0), std::domain_error, Message("(1, 0) does not fit within a matrix with dimensions (0, 0)"));
    CHECK_THROWS_MATCHES(m(0, 1), std::domain_error, Message("(0, 1) does not fit within a matrix with dimensions (0, 0)"));
}


TEST_CASE(".get() works as expected when not const-qualified") {
    auto m = matrix{
        {1, 1},
        {1, 1},
    };

    m(0, 0) = 0;
    m(1, 1) = 0;

    for (auto i = 0u; i < 2; ++i) {
        for (auto j = 0u; j < 2; ++j) {
            REQUIRE(m(i, j) == (i != j));
        }
    }
}


TEST_CASE(".get() works as expected when const-qualified") {
    const auto m = matrix{
        {1, 1, 1},
        {1, 1, 1},
        {1, 1, 1}
    };

    for (auto i = 0u; i < 3; ++i) {
        for (auto j = 0u; j < 3; ++j) {
            REQUIRE(m(i, j) == 1);
        }
    }
}


TEST_CASE("Can nothrow copy-assign a matrix") {
    CHECK(!std::is_nothrow_copy_assignable_v<matrix>);
}

TEST_CASE("Can copy assign a matrix") {
    auto m2 = matrix{};
    auto m1 = matrix{
        {1, 1, 1},
        {1, 1, 1},
        {1, 1, 1}
    };

    m2 = m1;
    CHECK(m1 == m2);
    
    SECTION("actually deep-copied") {
        m1(0, 0) = 4;

        CHECK(m2(0, 0) == 1);
    }
}

TEST_CASE("Matrix comparison is no-throw") {
    CHECK(std::is_nothrow_invocable_v<decltype(&matrix::operator==), const matrix &, const matrix &>);
}


TEST_CASE("Can compare matricies for equality") {
    auto m1 = matrix{
        {1, 1, 1},
        {1, 1, 1},
        {1, 1, 1}
    };
    auto m2 = matrix{
        {1, 1, 1},
        {1, 1, 1},
        {1, 1, 1}
    };
    auto m3 = matrix{
        {0, 1, 1},
        {1, 0, 1},
        {1, 1, 0}
    };

    for (auto i = 0u; i < 3; ++i) {
        for (auto j = 0u; j < 3; ++j) {
            REQUIRE(m1(i, j) == 1);
            REQUIRE(m2(i, j) == 1);
            REQUIRE(m3(i, j) == (i != j));
        }
    }

    CHECK(m1 == m2);
    CHECK(!(m1 == m3));
}


TEST_CASE("Can nothrow move-assign a matrix") {
    CHECK(std::is_nothrow_move_assignable_v<matrix>);
}


TEST_CASE("Can move assign a matrix") {
    auto m2 = matrix{};
    auto m1 = matrix{
        {1, 1, 1},
        {1, 1, 1},
        {1, 1, 1}
    };

    m2 = std::move(m1);

    CHECK(m1.dimensions() == std::make_pair<std::size_t, std::size_t>(0, 0));
    CHECK(m1.data_ == nullptr);

    const auto &[r, c] = m2.dimensions();
    REQUIRE((r == c && r == 3));

    for (auto i = 0u; i < r; ++i) {
        for (auto j = 0u; j < c; ++j) {
            REQUIRE(m2(i, j) == 1);
        }
    }
}


TEST_CASE("Can compare matricies for inequality") {
    auto m1 = matrix{
        {1, 1, 1},
        {1, 1, 1},
        {1, 1, 1}
    };
    auto m2 = matrix{
        {1, 1, 1},
        {1, 1, 1},
        {1, 1, 1}
    };
    auto m3 = matrix{
        {0, 1, 1},
        {1, 0, 1},
        {1, 1, 0}
    };

    for (auto i = 0u; i < 3; ++i) {
        for (auto j = 0u; j < 3; ++j) {
            REQUIRE(m1(i, j) == 1);
            REQUIRE(m2(i, j) == 1);
            REQUIRE(m3(i, j) == (i != j));
        }
    }

    CHECK(!(m1 != m2));
    CHECK(m1 != m3);
}

