#include "mixer.h"

auto wacky_colour(paint p1, paint p2) -> std::optional<paint>
{
    (void)p1;
    (void)p2;
    // remove the above two lines once implemented.

    return {};
}

auto mix(const std::vector<paint>& paints, std::function<std::optional<paint>(paint, paint)> fn) -> std::optional<paint>
{
    (void)paints;
    (void)fn;
    // remove the above two lines once implemented.

    return {};
}
