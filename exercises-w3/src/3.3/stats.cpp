#include "stats.h"
#include <algorithm>
#include <fstream>
#include <functional>
#include <iterator>
#include <numeric>

auto read_marks(const std::string& path) -> std::vector<int>
{
    auto ifs = std::ifstream{path};
    return std::vector<int>{std::istream_iterator<int>{ifs}, std::istream_iterator<int>{}};
}

auto calculate_stats(const std::vector<int>& marks) -> stats
{
    long sum = std::accumulate(marks.cbegin(), marks.cend(), 0);
    int avg = static_cast<int>(sum) / static_cast<int>(marks.size());

    auto copy = std::vector<int>{marks};
    std::sort(copy.begin(), copy.end());
    int mid = copy.at(copy.size() / 2);

    int highest = *std::max_element(marks.cbegin(), marks.cend());
    int lowest = *std::min_element(marks.cbegin(), marks.cend());

    return stats{
        .avg = avg,
        .median = mid,
        .highest = highest,
        .lowest = lowest
        // .highest = *(copy.rbegin()),
        // .highest = *(--copy.end()),
        
    };
}