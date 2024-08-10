#ifndef COMP6771_Q1_H
#define COMP6771_Q1_H

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <iterator>
#include <stdexcept>
#include <type_traits>
#include <vector>
#include <string>

namespace q1 {

struct value {
    double num;
    bool is_double;
    value(double n, bool d): num{n}, is_double{d} {} 
};

inline auto process(std::vector<value>& stack, const std::string& input) -> void {
    if (input == std::string("add")) {
        const auto& y = stack.back();
        stack.pop_back(); 

        const auto& x = stack.back();
        stack.pop_back();

        const auto answer = x.num + y.num;
        stack.emplace_back(answer, x.is_double || x.is_double); 
    } else if (input == std::string("sub")) {
        const auto& y = stack.back();
        stack.pop_back(); 

        const auto& x = stack.back();
        stack.pop_back();

        const auto answer = x.num - y.num;
        stack.emplace_back(answer, x.is_double || x.is_double); 

    } else if (input == std::string("mult")) {
        const auto& y = stack.back();
        stack.pop_back(); 

        const auto& x = stack.back();
        stack.pop_back();

        const auto answer = x.num * y.num;
        stack.emplace_back(answer, x.is_double || x.is_double); 

    } else if (input == std::string("div")) {
        const auto& y = stack.back();
        stack.pop_back(); 

        const auto& x = stack.back();
        stack.pop_back();

        const auto answer = x.num / y.num;
        bool is_double = false;
        if (static_cast<int>(answer) != answer) {
            is_double = true;
        }

        if (not x.is_double && not x.is_double && not is_double) {
            stack.emplace_back(answer, false); 
        } else {
            stack.emplace_back(answer, true); 
        }

    } else if (input == std::string("sqrt")) {
        const auto& x = stack.back();
        stack.pop_back();
        
        const auto answer = std::sqrt(x.num);
        stack.emplace_back(answer, true); 

    } else if (input == std::string("pop")) {
        stack.pop_back();
    } else if (input == std::string("reverse")) {
        std::reverse(stack.begin(), stack.end());
    } else {
        // number
        const auto answer = std::stod(input);
        bool is_double = false;
        if (static_cast<int>(answer) != answer) {
            is_double = true;
        }
        stack.emplace_back(answer, is_double); 
    }
}
inline auto calculate(const std::vector<std::string>& inputs) -> double {
    auto stack = std::vector<value>{};

    for (const auto& input : inputs) {
        process(stack, input);
        
    }

    if (not stack.empty()) {
        return stack.back().num;
    }
    return 0;
}

}
#endif // COMP6771_Q1_H