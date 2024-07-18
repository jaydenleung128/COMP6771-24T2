#ifndef COMP6771_MATRIX_H
#define COMP6771_MATRIX_H

#include <algorithm>
#include <memory>
#include <stdexcept>
#include <utility>
class matrix {
public:
matrix() noexcept = default;

matrix(std::initializer_list<std::initializer_list<int>> il) {
    n_rows_ = il.size();
    n_cols_ = il.begin()->size();
    data_ = std::make_unique<int[]>(n_rows_ * n_cols_);

    // for (const auto& inner: il) {
    //     if (inner.size() != n_cols_) {
    //         throw std::logic_error("Columns are not equal length");
    //     }
    // }

    if (!std::all_of(il.begin(), il.end(), [this](const auto& inner){
        return inner.size() == n_cols_;
    })) {
        throw std::logic_error("Columns are not equal length");
    }

    auto i = std::size_t{0};
    for (const auto& inner: il) {
        std::copy(inner.begin(), inner.end(), data_.get() + i);
        i += n_cols_;
    }
}

/* 3 */ matrix(const matrix &other);
/* 4 */ matrix(matrix &&other);

private:

std::unique_ptr<int[]> data_;
std::size_t n_rows_;
std::size_t n_cols_;
};

#endif // COMP6771_MATRIX_H
