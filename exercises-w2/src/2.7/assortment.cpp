#include "assortment.h"
#include <vector>

auto sort(std::vector<int>& ivec) -> void
{
    std::sort(ivec.begin(), ivec.end());
}

auto sort(std::array<int, 4>& iarr) -> void
{
    std::sort(iarr.begin(), iarr.end());
}

auto sort(std::list<int>& ilist) -> void
{
    auto temp = std::vector<int>{ilist.begin(), ilist.end()};
    std::sort(temp.begin(), temp.end());
    ilist = std::list<int>{temp.begin(), temp.end()};
}