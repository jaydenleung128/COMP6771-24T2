#include <catch2/catch.hpp>
#include <iostream>

#include "microbenchmark.h"

constexpr int N_REPS = 3;

TEST_CASE("printing the time out and also basic sanity check on the timings") {
    constexpr int N_ELEMS = 2'500'000; // 250k

    const auto &[l_time, d_time, v_time] = microbenchmark_lookup(N_REPS, N_ELEMS);

    std::cout << l_time << " " << d_time << " " << v_time << std::endl;

    CHECK((v_time > 0 && d_time > 0 && l_time > 0));
}

/*
 * One could feasibly continue benchmarking here, but there are many variables out of our control.
 * One is the randomness of how close the targets happen to lie to the front of the container.
 * Another is the individual CPU / cache / implementations of the standard library.
 * The purpose of this exercise was to get some experience writing a benchmark...
 * ... but now I hope you appreciate how difficult it actually is to benchmark properly!
 */
