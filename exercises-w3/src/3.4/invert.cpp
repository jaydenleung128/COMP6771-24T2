#include "invert.h"

auto invert(const std::map<std::string, int>& mp) -> std::map<int, std::string>
{
    auto ret = std::map<int, std::string>{};
    for (const auto& [a, b]: mp) {
        // std::string a = x.first;
        // int b = x.second;

        if (!ret.contains(b)) {
            ret.emplace(b, a);
        } 
    }


    (void)mp;
    return ret;
}