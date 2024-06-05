#include "fib_vector.h"

auto fibonacci(int n) -> std::vector<int>
{
    auto nums = std::vector<int> { n };

    nums.push_back(42);

    return nums;
}
