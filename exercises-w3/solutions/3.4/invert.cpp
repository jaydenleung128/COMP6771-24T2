#include "invert.h"

#include <iostream>

auto invert(const std::map<std::string, int> &mp) -> std::map<int, std::string> {
    auto inverted = std::map<int, std::string>{};

    for (const auto &[k, v] : mp) {
        if (auto it = inverted.find(v); it != inverted.end()) {
            if (it->second.size() < k.size()) {
                inverted[v] = k;
            } else {
                // no change, current "k" isn't the longest string we've seen for this "v"
            }
        } else {
            inverted.insert({v, k});
        }
    }

    return inverted;
}
