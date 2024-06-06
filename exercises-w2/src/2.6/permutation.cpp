#include "permutation.h"
#include <unordered_map>

auto is_permutation(const std::string& x, const std::string& y) -> bool
{
    auto counter1 = std::unordered_map<char, int>{};
    auto counter2 = std::unordered_map<char, int>{};

    for (auto const& character: x) {
        if (!counter1.contains(character)) {
            counter1.emplace(character, 0);
        }
        counter1.emplace(character, counter1.at(character) + 1);
    }

    for (auto const& character: y) {
        if (!counter2.contains(character)) {
            counter2.emplace(character, 0);
        }
        counter2.emplace(character, counter2.at(character) + 1);
    }

    return counter1 == counter2;
}
