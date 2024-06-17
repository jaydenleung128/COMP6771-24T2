#include "sort_descending.h"
#include <algorithm>

auto sort_descending(std::vector<int>& numbers) -> void
{
    // std::reverse(numbers.begin(), numbers.end());
    std::sort(numbers.begin(), numbers.end(), std::greater<>());
}
