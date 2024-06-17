#include "vsort.h"
#include <functional>

auto vsort(std::vector<std::string>& vs) -> void
{   
    std::sort(vs.begin(), vs.end(), [](const std::string& a, const std::string& b) -> bool {

        const auto countVowels = [](char c) -> bool {
            return c == 'a' or c == 'e' or c == 'i' or c == 'o' or c == 'u';
        };

        // sort by num vowels
        long countA = std::count_if(a.begin(), a.end(), countVowels);

        long countB = std::count_if(b.begin(), b.end(), countVowels);

        if (countA != countB) {
            return countA < countB;
        } else {
            // sort by string
            return a < b;
        }
    });
}