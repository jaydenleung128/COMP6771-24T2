#ifndef COMP6771_RATIONAL_OO_H
#define COMP6771_RATIONAL_OO_H

#include <optional>


class rational_number {
public:
    static std::optional<rational_number> null;

    static auto make_rational(int numerator, int denominator) -> std::optional<rational_number> {
        if (denominator == 0) {
            return null;
        } else {
            return std::optional<rational_number>{rational_number{numerator, denominator}};
        }
    }

    auto operator[](char c) -> int& { return c == '^' ? numerator_ : denominator_; }
    
    auto operator[](char c) const -> const int& { return c == '^' ? numerator_ : denominator_; }

    operator double() const {
        return static_cast<double>(numerator_) / denominator_;
    }

    friend auto operator+(const rational_number &lhs, const rational_number &rhs) -> rational_number {
        auto ad = lhs.numerator_ * rhs.denominator_;
        auto bc = lhs.denominator_ * rhs.numerator_;
        auto bd = lhs.denominator_ * rhs.denominator_;

        return rational_number(ad + bc, bd);
    }

    friend auto operator-(const rational_number &lhs, const rational_number &rhs) -> rational_number {
        auto ad = lhs.numerator_ * rhs.denominator_;
        auto bc = lhs.denominator_ * rhs.numerator_;
        auto bd = lhs.denominator_ * rhs.denominator_;

        return rational_number(ad - bc, bd);
    }

    friend auto operator*(const rational_number &lhs, const rational_number &rhs) -> rational_number {
        auto ac = lhs.numerator_ * rhs.numerator_;
        auto bd = lhs.denominator_ * rhs.denominator_;

        return rational_number(ac, bd);
    }

    friend auto operator/(const rational_number &lhs, const rational_number &rhs) -> std::optional<rational_number> {
        auto ad = lhs.numerator_ * rhs.denominator_;
        auto bc = lhs.denominator_ * rhs.numerator_;

        return make_rational(ad, bc);
    }

    friend auto operator==(const rational_number &lhs, const rational_number &rhs) -> bool {
        auto ad = lhs.numerator_ * rhs.denominator_;
        auto bc = lhs.denominator_ * rhs.numerator_;
        return ad == bc;
    }

    friend auto operator!=(const rational_number &lhs, const rational_number &rhs) -> bool {
        return !(lhs == rhs);
    }

private:
    rational_number(int numerator, int denominator) : numerator_{numerator}, denominator_{denominator} {}

    int numerator_;
    int denominator_;
};

#endif // COMP6771_RATIONAL_OO_H
