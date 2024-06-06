#include "mismatch.h"

auto mismatch(std::vector<int> &v1, std::vector<int> &v2) -> std::pair<iter, iter> {
    auto iter1 = v1.begin(), last1 = v1.end();
    auto iter2 = v2.begin(), last2 = v2.end();

    while(iter1 != last1 && iter2 != last2 && *iter1 == *iter2) {
        iter1++;
        iter2++;
    }

    return std::make_pair(iter1, iter2);
}
