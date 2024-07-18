#ifndef COMP6771_BOOK_H
#define COMP6771_BOOK_H

#include <cmath>
#include <iomanip>
#include <string>

class book {
public:
    book(const std::string &name, const std::string &author, const std::string &isbn, double price)
    : name_{name}, author_{author}, isbn_{isbn}, price_{price} {}

    explicit operator std::string() const {
        return author_ + ", " + name_;
    }

    const std::string &name() const {
        return name_;
    }
    const std::string &author() const {
        return author_;
    }
    const std::string &isbn() const {
        return isbn_;
    }
    const double &price() const {
        return price_;
    }

    friend bool operator==(const book &lhs, const book &rhs) {
        return lhs.isbn_ == rhs.isbn_;
    }

    friend bool operator!=(const book &lhs, const book &rhs) {
        return !(lhs == rhs);
    }

    friend bool operator<(const book &lhs, const book &rhs) {
        return lhs.isbn_ < rhs.isbn_;
    }

    friend std::ostream &operator<<(std::ostream &os, const book &b) {
        double rounded_price = b.price_ - static_cast<int>(b.price_); // remove integer part
               rounded_price = std::round(rounded_price * 100) / 100; // round the fractional part
               rounded_price = static_cast<int>(b.price_) + rounded_price; // get the final rounded value

        os << b.name_ << ", "
           << b.author_ << ", "
           << b.isbn_ << ", $"
           << std::fixed << std::setprecision(2) << rounded_price;
        return os;
    }

private:
    std::string name_;
    std::string author_;
    std::string isbn_;
    double price_;
};

#endif // COMP6771_BOOK_H

