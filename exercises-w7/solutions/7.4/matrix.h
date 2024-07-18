#ifndef COMP6771_MATRIX_H
#define COMP6771_MATRIX_H

#include <algorithm>
#include <exception>
#include <initializer_list>
#include <memory>
#include <sstream>

class matrix {
public:
    matrix() noexcept = default;
    
    matrix(std::initializer_list<std::initializer_list<int>> il) {
        const std::size_t r = il.size();
        const std::size_t c = il.begin()->size();

        if (!std::all_of(il.begin() + 1, il.end(), [c](const std::initializer_list<int> il) {
            return il.size() == c;
        })) {
            throw std::logic_error{col_len_msg()};
        }

        std::unique_ptr<int[]> data = std::make_unique<int[]>(r * c);
        int *p = data.get();
        for (const std::initializer_list<int> &col : il) {
            for (int i : col) {
                *p++ = i;
            }
        }

        data_ = std::move(data);
        n_rows_ = std::move(r);
        n_cols_ = std::move(c);
    }

    matrix(const matrix &o)
    : data_{std::make_unique<int[]>(o.n_rows_ * o.n_cols_)},
    n_rows_{o.n_rows_},
    n_cols_{o.n_cols_} {
        std::copy(o.begin(), o.end(), begin());
    }

    matrix(matrix &&o) noexcept
    : data_{std::exchange(o.data_, nullptr)},
    n_rows_{std::exchange(o.n_rows_, 0)},
    n_cols_{std::exchange(o.n_cols_, 0)} {}

    matrix &operator=(const matrix &o) {
        if (this != &o) {
            *this = matrix{o};
        }

        return *this;
    }

    matrix &operator=(matrix &&o) noexcept {
        if (this != &o) {
            data_ = std::exchange(o.data_, nullptr);
            n_rows_ = std::exchange(o.n_rows_, 0);
            n_cols_ = std::exchange(o.n_cols_, 0);
        }

        return *this;
    }

    const int &operator()(std::size_t i, std::size_t j) const {
        if (!(i < n_rows_ && j < n_cols_)) {
            throw std::domain_error{bounds_msg(i, n_rows_, j, n_cols_)};
        }
        return data_[i * n_cols_ + j];
    }

    int &operator()(std::size_t r, std::size_t c) {
        if (!(r < n_rows_ && c < n_cols_)) {
            throw std::domain_error{bounds_msg(r, n_rows_, c, n_cols_)};
        }

        return data_[r * n_cols_ + c];
    }

    bool operator==(const matrix &r) const noexcept {
        const matrix &l = *this;
        return l.n_rows_ == r.n_rows_
            && l.n_cols_ == r.n_cols_
            && std::equal(l.begin(), l.end(), r.begin());
    }

    std::pair<std::size_t, std::size_t> dimensions() const noexcept {
        return std::make_pair(n_rows_, n_cols_);
    }

    const int *data() const noexcept {
        return data_.get();
    }

private:
    std::string bounds_msg(std::size_t i, std::size_t r, std::size_t j, std::size_t c) const {
        std::stringstream ss;
        ss << "(" << i << ", " << j << ")"
           << " does not fit within a matrix with dimensions "
           << "(" << r << ", " << c << ")";
        return ss.str();
    }

    std::string col_len_msg() const {
        return "Columns are not equal length";
    }

    std::size_t length() const {
        return n_rows_ * n_cols_;
    }

    int *begin() { return data_.get(); }
    int *end() { return begin() + length(); }
    const int *begin() const { return data_.get(); }
    const int *end() const { return begin() + length(); }

    std::unique_ptr<int[]> data_;
    std::size_t n_rows_;
    std::size_t n_cols_;
};

#endif // COMP6771_MATRIX_H
