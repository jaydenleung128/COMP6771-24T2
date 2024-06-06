#include "scale.h"
#include <vector>

auto scale(const std::vector<int>& ivec, double factor) -> std::vector<double>
{   
    // const auto a = 1;
    // auto const b = 2;
    auto v = std::vector<double>{};

    for (auto const& i: ivec) {
        double new_number = static_cast<double>(i) * factor;
        v.push_back(new_number);
    }

    return v;
}
