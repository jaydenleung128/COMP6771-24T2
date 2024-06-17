#include "./stats.h"

#include <algorithm>
#include <fstream>
#include <iterator>
#include <numeric>

auto read_marks(const std::string &path) -> std::vector<int> {
    auto fp = std::ifstream{path};

    // vector::vector(InputIt start, InputIt end) constructor is very useful
    return std::vector<int>{
        std::istream_iterator<int>{fp},
        std::istream_iterator<int>{}
    };
}

auto calculate_stats(const std::vector<int> &marks) -> stats {
    auto sorted_marks = marks;
    std::sort(sorted_marks.begin(), sorted_marks.end());
    return {
        .avg = std::accumulate(marks.begin(), marks.end(), 0) / static_cast<int>(marks.size()),
        .median = sorted_marks[sorted_marks.size() / 2],
        .highest = sorted_marks.back(),
        .lowest = sorted_marks.front(),
    };
}
