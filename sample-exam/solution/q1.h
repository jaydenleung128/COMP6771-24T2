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
enum token {
    NUMBER,
    ADD,
    SUB,
    MULT,
    DIV,
    SQRT,
    POP,
    REVERSE,
    REPEAT,
    ENDREPEAT,
};

struct value {
    double num;
    bool is_double;

    value(double n, bool d): num{n}, is_double{d} {}
};

inline auto print_stack(std::vector<value>& stack) {
    for (const auto& v: stack) {
        std::cout << v.num << ' ';
    }
    std::cout << '\n';
}

inline auto process(const std::string& s, std::vector<value>& stack) -> void {
    if (s == std::string("add")) {
        const auto y = stack.back();
        stack.pop_back();

        const auto x = stack.back();
        stack.pop_back();

        const auto z = x.num + y.num; 
        stack.emplace_back(z, x.is_double || y.is_double);
    } else if (s == std::string("sub")) {
        const auto y = stack.back();
        stack.pop_back();

        const auto x = stack.back();
        stack.pop_back();

        stack.emplace_back(x.num - y.num, x.is_double || y.is_double);
        std::cout << x.num - y.num << " - " << y.num << '\n';

    } else if (s == std::string("mult")) {
        const auto y = stack.back();
        stack.pop_back();

        const auto x = stack.back();
        stack.pop_back();

        stack.emplace_back(x.num * y.num, x.is_double || y.is_double);
    } else if (s == std::string("div")) {
        const auto y = stack.back();
        stack.pop_back();

        const auto x = stack.back();
        stack.pop_back();
        if (x.is_double || y.is_double) {
            // Promote to double
            stack.emplace_back(static_cast<double>(x.num) / static_cast<double>(y.num), true);
        } else {
            stack.emplace_back(x.num / y.num, false);
        }

    } else if (s == std::string("sqrt")) {
        const auto x = stack.back();
        stack.pop_back();
        stack.emplace_back( std::sqrt(x.num), true);

    } else if (s == std::string("pop")) {
        stack.pop_back();
    } else if (s == std::string("reverse")) {
        std::reverse(stack.begin(), stack.end());
    } else {
        try {
            double d = std::stod(s);
            stack.emplace_back(d, std::floor(d) == d);
        } catch (...) {
            throw std::runtime_error("invalid arg");
        }
    }

    print_stack(stack);
}

inline auto loop(const std::vector<std::string>& inputs, std::vector<value>& stack, std::vector<std::string>::const_iterator begin, std::vector<std::string>::const_iterator end, std::size_t remaining_iterations) -> void {
    bool is_repeating = false;
    std::size_t repeat_iterations = 0;
    std::vector<std::string>::const_iterator repeat_start;
    auto it = begin;

    while (it != end) {
        if (*it == std::string("repeat")) {
            is_repeating = true;
            repeat_start = it + 1;
            repeat_iterations = static_cast<std::size_t>(stack.back().num);
            stack.pop_back();
        } else if (*it == std::string("endrepeat")) {
            is_repeating = false;
            loop(inputs, stack, repeat_start, it, repeat_iterations - 1);
        } else {
            if (!is_repeating) {
                process(*it, stack);
            }
        }

        ++it;
    }

    if (remaining_iterations > 0) {
        loop(inputs, stack, begin, end, remaining_iterations - 1);
    }
}

inline auto calculate(const std::vector<std::string>& inputs) -> double {
    auto stack = std::vector<value>{};
    
    loop(inputs, stack, inputs.cbegin(), inputs.cend(), 0);

    if (not stack.empty()) {
        return stack.at(0).num;
    }
    return 0.0;
}

}
#endif // COMP6771_Q1_H