#ifndef COMP6771_RATIONAL_H
#define COMP6771_RATIONAL_H

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

    auto value() const -> double {
        return static_cast<double>(numerator_) / static_cast<double>(denominator_);
    }

    friend auto add(const rational_number &lhs, const rational_number &rhs) -> rational_number {
        auto ad = lhs.numerator_ * rhs.denominator_;
        auto bc = lhs.denominator_ * rhs.numerator_;
        auto bd = lhs.denominator_ * rhs.denominator_;

        return rational_number(ad + bc, bd);
    }

    friend auto sub(const rational_number &lhs, const rational_number &rhs) -> rational_number {
        auto ad = lhs.numerator_ * rhs.denominator_;
        auto bc = lhs.denominator_ * rhs.numerator_;
        auto bd = lhs.denominator_ * rhs.denominator_;

        return rational_number(ad - bc, bd);
    }

    friend auto mul(const rational_number &lhs, const rational_number &rhs) -> rational_number {
        auto ac = lhs.numerator_ * rhs.numerator_;
        auto bd = lhs.denominator_ * rhs.denominator_;

        return rational_number(ac, bd);
    }

    friend auto div(const rational_number &lhs, const rational_number &rhs) -> std::optional<rational_number> {
        auto ad = lhs.numerator_ * rhs.denominator_;
        auto bc = lhs.denominator_ * rhs.numerator_;

        return make_rational(ad, bc);
    }

    friend auto eq(const rational_number &lhs, const rational_number &rhs) -> bool {
        auto ad = lhs.numerator_ * rhs.denominator_;
        auto bc = lhs.denominator_ * rhs.numerator_;
        return ad == bc;
    }

    friend auto ne(const rational_number &lhs, const rational_number &rhs) -> bool {
        return !eq(lhs, rhs);
    }

private:
    rational_number(int numerator, int denominator) : numerator_{numerator}, denominator_{denominator} {}

    int numerator_;
    int denominator_;
};

#endif // COMP6771_RATIONAL_H
