#include <utility>
#include <vector>

#include "mismatch.h"

auto mismatch(std::vector<int>& v1, std::vector<int>& v2) -> std::pair<iter, iter>
{
    auto it1 = v1.begin();
    auto it2 = v2.begin();

    while (it1 != v1.end() && it2 != v2.end()) {
        if (*it1 != *it2) {
            return std::make_pair(it1, it2);
        }
        ++it1;
        ++it2;
    }

    return std::make_pair(v1.begin(), v2.begin());
}