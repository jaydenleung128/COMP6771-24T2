#ifndef COMP6771_RING_H
#define COMP6771_RING_H

#include <stdexcept>
#include <cstddef>
#include <initializer_list>
#include <string>

template <typename T, std::size_t N>
class ring {
public:
    template <typename InputIt>
    ring(InputIt first, InputIt last) : head_{0}, tail_{0}, size_{0} {
        if (static_cast<std::size_t>(std::distance(first, last)) > N) {
            throw std::invalid_argument{"Not enough capacity"};
        }
        for (; first != last; ++first)
            do_push(*first);
    }

    ring(std::initializer_list<T> il) : ring(il.begin(), il.end()) {}

    auto push(const T &t) -> void {
        if (size_ < N) {
            do_push(t);
        }
    }

    auto peek() const -> const T& {
        return elems_[head_];
    }

    auto pop() -> void {
        if (size_ > 0) {
            do_pop();
        }
    }

    auto size() const -> std::size_t {
        return size_;
    }

private:
    auto do_push(const T &t) {
        elems_[tail_++] = t;
        tail_ %= N;
        size_++;
    }

    auto do_pop() {
        head_ = ++head_ % N;
        size_--;
    }

    std::size_t head_; 
    std::size_t tail_; 
    std::size_t size_; 
    T elems_[N];
};

template <typename T, typename ...Ts>
ring(T, Ts...) -> ring<T, sizeof...(Ts) + 1>;

#endif // COMP6771_RING_H

