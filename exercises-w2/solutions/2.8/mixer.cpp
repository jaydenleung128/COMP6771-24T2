#include "mixer.h"

auto wacky_colour(paint p1, paint p2) -> std::optional<paint> {
    auto ret = std::optional<paint>{};

    if (p1 == paint::RED && p2 == paint::GREEN) {
        ret.emplace(paint::YELLOW);
    } else if (p1 == paint::RED && p2 == paint::BLUE) {
        ret.emplace(paint::MAGENTA);
    } else if (p1 == paint::GREEN && p2 == paint::BLUE) {
        ret.emplace(paint::CYAN);
    } else if (p1 == paint::YELLOW && p2 == paint::MAGENTA) {
        ret.emplace(paint::BROWN);
    } else if (p1 == paint::YELLOW && p2 == paint::CYAN) {
        ret.emplace(paint::BROWN);
    } else if (p1 == paint::CYAN && p2 == paint::MAGENTA) {
        ret.emplace(paint::BROWN);
    } else if (p1 == paint::BROWN && p2 == paint::BROWN) {
        ret.emplace(paint::BROWN);
    }

    return ret;
}


auto mix(const std::vector<paint> &paints, std::function<std::optional<paint>(paint, paint)> fn) -> std::optional<paint> {
    auto new_paint = std::optional<paint>{paints.front()};
    for (auto i = 1u; i < paints.size() && new_paint.has_value(); ++i) {
        new_paint = fn(*new_paint, paints[i]);
    }

    return new_paint;
}
