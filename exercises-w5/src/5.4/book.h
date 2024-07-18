#ifndef COMP6771_BOOK_H
#define COMP6771_BOOK_H

#include <cmath>
#include <iomanip>
#include <string>

class book {
public:
    book(const std::string &name, const std::string &author, const std::string &isbn, double price):
    name_{name}, author_{author}, isbn_{isbn}, price_{price} {};

    explicit operator std::string() const {
        return author_ + ", " + name_;
    }

    auto name() const -> const std::string& {
        return name_;
    }

    auto author() const -> const std::string& {
        return author_;
    }

    auto isbn() const -> const std::string& {
        return isbn_;
    }

    auto price() const -> const double& {
        return price_;
    }

    friend bool operator==(const book &lhs, const book &rhs) {
        return lhs.name_ == rhs.name_ && lhs.author_ == rhs.author_ && lhs.isbn_ == rhs.isbn_ && lhs.price_ == rhs.price_;
    }

    friend bool operator!=(const book &lhs, const book &rhs) {
        return not(lhs == rhs);
    }

    friend bool operator<(const book &lhs, const book &rhs) {
        return lhs.price_ < rhs.price_;
    }

    friend std::ostream &operator<<(std::ostream &os, const book &b) {
        os << b.name_;
        os << ", ";
        os << b.author_;
        os << ", ";
        os << b.isbn_;
        os << ", $";
        os << b.price_;
        return os;
    }
    
private:
    std::string name_;
    std::string author_;
    std::string isbn_;
    double price_;
};

#endif // COMP6771_BOOK_H

