#include "microbenchmark.h"

#include <chrono>
#include <random>

constexpr auto LOWER_BOUND = 0;
constexpr auto UPPER_BOUND = 500'000; // C++11 onwards allows ' as a number separator

// A useful function to generate random numbers in a mathematically sound way
auto rand() -> int {
    static auto rd = std::random_device{};   // Will be used to obtain a seed for the random number engine
    static auto gen = std::mt19937(rd());      // Standard mersenne_twister_engine seeded with rd()
    static auto distrib = std::uniform_int_distribution<>(LOWER_BOUND, UPPER_BOUND);

    return distrib(gen);
}

auto make_nums(int n_elems) -> std::vector<int> {
    auto nums = std::vector<int>{};
    nums.reserve(static_cast<std::size_t>(n_elems));
    for (auto j = 0; j < n_elems; ++j)
        nums.push_back(rand());
    return nums;
}

auto microbenchmark_lookup(int n_repetitions, int n_elems) -> timings {
    using nanosecond_t = std::chrono::duration<double, std::nano>;

    auto l_timings = std::vector<double>{};
    auto d_timings = std::vector<double>{};
    auto v_timings = std::vector<double>{};

    for (auto i = 0; i < n_repetitions; ++i) {
        auto nums = make_nums(n_elems);
        auto target = rand();
        
        auto l = std::list<int>{nums.begin(), nums.end()};
        auto d = std::deque<int>{nums.begin(), nums.end()};
        auto v = std::vector<int>{nums.begin(), nums.end()};

        {
            auto then = std::chrono::steady_clock::now();
            (void) std::find(l.begin(), l.end(), target);
            auto now = std::chrono::steady_clock::now();
            auto time_taken = std::chrono::duration_cast<nanosecond_t>(now - then).count();
            l_timings.push_back(time_taken);
        }   

        {
            auto then = std::chrono::steady_clock::now();
            (void) std::find(d.begin(), d.end(), target);
            auto now = std::chrono::steady_clock::now();
            auto time_taken = std::chrono::duration_cast<nanosecond_t>(now - then).count();
            d_timings.push_back(time_taken);
        }      

        {
            auto then = std::chrono::steady_clock::now();
            (void) std::find(v.begin(), v.end(), target);
            auto now = std::chrono::steady_clock::now();
            auto time_taken = std::chrono::duration_cast<nanosecond_t>(now - then).count();
            v_timings.push_back(time_taken);
        }
    }

    return timings {
        .list_avg_time = std::accumulate(l_timings.begin(), l_timings.end(), 0.0) / static_cast<double>(n_repetitions),
        .deque_avg_time = std::accumulate(d_timings.begin(), d_timings.end(), 0.0) / static_cast<double>(n_repetitions),
        .vec_avg_time = std::accumulate(v_timings.begin(), v_timings.end(), 0.0) / static_cast<double>(n_repetitions)
    };
}

