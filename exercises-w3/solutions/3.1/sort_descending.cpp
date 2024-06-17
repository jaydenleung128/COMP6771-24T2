#include "./sort_descending.h"

#include <functional>

auto sort_descending(std::vector<int>& numbers) -> void {
    // why write any custom code when the standard library has your back?
    std::sort(numbers.begin(), numbers.end(), std::greater<>{});
}
