#include "assortment.h"


auto sort(std::vector<int> &ivec) -> void {
    std::sort(ivec.begin(), ivec.end());
}

auto sort(std::array<int, 4> &iarr) -> void {
    std::sort(iarr.begin(), iarr.end());
}

auto sort(std::list<int> &ilist) -> void {
    auto ivec = std::vector<int>(ilist.begin(), ilist.end());
    std::sort(ivec.begin(), ivec.end());
    std::copy(ivec.begin(), ivec.end(), ilist.begin());
}
