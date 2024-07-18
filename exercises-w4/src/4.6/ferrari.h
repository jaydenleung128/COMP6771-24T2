#ifndef COMP6771_FERRARIPP_H
#define COMP6771_FERRARIPP_H
#include <string>

class ferrari {
public:

ferrari() : ferrari("unknown", 6771) {};
ferrari(const std::string &owner, int modelno) : owner_{owner}, model_number_{modelno}, speed_{0} {};

auto get_details() const -> std::pair<std::string, int>;

auto drive(int spd = 80) -> void;
auto vroom() -> std::string;

private:
    std::string owner_;
    int model_number_;
    int speed_;
};

#endif  // COMP6771_FERRARIPP_H