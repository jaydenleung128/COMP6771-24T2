#include "microbenchmark.h"

#include <random>

constexpr auto LOWER_BOUND = 0;
constexpr auto UPPER_BOUND = 500'000; // C++11 onwards allows ' as a number separator

// A useful function to generate random numbers in a mathematically sound way
auto rand() -> int
{
    static auto rd = std::random_device {}; // Will be used to obtain a seed for the random number engine
    static auto gen = std::mt19937(rd()); // Standard mersenne_twister_engine seeded with rd()
    static auto distrib = std::uniform_int_distribution<>(LOWER_BOUND, UPPER_BOUND);

    return distrib(gen);
}

auto microbenchmark_lookup(int n_repetitions, int n_elems) -> timings
{
    (void)n_repetitions;
    (void)n_elems;
    return {};
}
