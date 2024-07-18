#ifndef COMP6771_FERRARIPP_H
#define COMP6771_FERRARIPP_H

#include <string>
#include <utility>

class ferrari {
public:
    ferrari() : ferrari("unknown", 6771, 0) {}
    ferrari(const std::string &owner, int modelno) : ferrari(owner, modelno, 0) {}

    auto get_details() const -> std::pair<std::string, int> {
        return std::make_pair(owner_, modelno_);
    }
    
    auto drive(int spd = 88) -> void {
        speed_ = spd;
    }
    
    auto vroom() const -> std::string { 
        if (speed_ < 20) {
            return "";
        } else if (speed_ < 80) {
            return "vroom!!";
        } else {
            return "VROOOOOOOOM!!!";
        }
    }

private:
    ferrari(const std::string &owner, int modelno, int spd)
    : owner_{owner}, modelno_{modelno}, speed_{spd} {}

    std::string owner_;
    int modelno_;
    int speed_;

};

#endif  // COMP6771_FERRARIPP_H
