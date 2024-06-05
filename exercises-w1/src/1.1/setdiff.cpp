#include "setdiff.h"

#include <algorithm>
#include <iostream>
#include <vector>

auto set_difference(std::vector<char>& vec_set, const std::vector<char>& blacklist) -> void
{
    // std::vector<char> vec;
    auto temp = std::vector<char>{};
    for (auto const c: vec_set) {
        if (std::find(blacklist.cbegin(), blacklist.cend(), c) != blacklist.cend()) {
            continue;
        }
        temp.push_back(c);
    }
    std::cout << temp.size();
    vec_set = temp;
}
