#include "fib_vector.h"

auto fibonacci(int n) -> std::vector<int> {
    auto nums = std::vector<int>{};

    for (int k_2 = 0, k_1 = 1; n > 0; --n) {
        int nth = k_2 + k_1;
        nums.push_back(nth);
        k_2 = k_1;
        k_1 = nth;
    }

    return nums;
}


