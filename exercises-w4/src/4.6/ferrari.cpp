#include "./ferrari.h"
#include <utility>

auto ferrari::get_details() -> std::pair<std::string, int> {
    return std::make_pair(owner_, model_number_);
}

auto ferrari::drive(int spd) -> void {
    speed_ = spd;
}

auto ferrari::vroom() -> std::string {
    if (speed_ < 20) return "";
    if (speed_ < 80) return "vroom!!";
    return "VROOOOOOM!!!";
}
