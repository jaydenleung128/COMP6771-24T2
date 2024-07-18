#ifndef COMP6771_ZIP_H
#define COMP6771_ZIP_H

#include <iterator>
#include <vector>

using ivec = std::vector<int>;

class zip {
    class iter {
        friend zip;
    public:
        using iterator_category = std::random_access_iterator_tag;
        using value_type = std::pair<int, int>;
        using reference = std::pair<int, int>;
        using pointer = void;
        using difference_type = std::ptrdiff_t;

        iter() = default;

        reference operator*() const {
            return (*this)[0];
        }

        pointer operator->() const { /* do nothing */ }

        iter &operator++() {
            ++ix_;
            return *this;
        }
        
        iter operator++(int) {
            auto self = *this;
            ++*this;
            return self;
        }

        iter &operator--() {
            --ix_;
            return *this;
        }

        iter operator--(int) {
            auto self = *this;
            --*this;
            return self;
        }
        
        iter &operator+=(int n) {
            ix_ += static_cast<std::size_t>(n);
            return *this;
        }

        iter &operator-=(int n) {
            ix_ -= static_cast<std::size_t>(n);
            return *this;
        }
        
        reference operator[](int n) const {
            std::size_t N = static_cast<std::size_t>(n);
            return std::make_pair((*l_)[ix_ + N], (*r_)[ix_ + N]);
        }
        
        friend iter operator+(iter i, int n) {
            return i += n;
        }

        friend iter operator+(int n, iter i) {
            return i + n;
        }

        friend iter operator-(iter i, int n) {
            return i + -n;
        }

        friend difference_type operator-(iter l, iter r) {
            return static_cast<difference_type>(l.ix_ - r.ix_);
        }

        // defaulting operator<=> will synthesise all 6 comparison functions
        auto operator<=>(const iter &) const = default;

    private:
        iter(const ivec *l, const ivec *r, std::size_t ix) : l_{l}, r_{r}, ix_{ix} {}

        const ivec *l_;
        const ivec *r_;
        std::size_t ix_;
    };

public:
    using iterator = iter;
    using const_iterator = iter;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    zip() = default;

    zip(const ivec &rng1, const ivec &rng2)
    : lhs_{&rng1}, rhs_{&rng2}, len_{std::min(rng1.size(), rng2.size())} {}

	auto begin() -> iterator {
		return { lhs_, rhs_, 0 };
	}
	
	auto end() -> iterator {
		return { lhs_, rhs_, len_ };
	}

	auto begin() const -> const_iterator {
		return { lhs_, rhs_, 0 };
	}

	auto end() const -> const_iterator {
		return { lhs_, rhs_, len_ };
	}

	auto cbegin() const -> const_iterator {
		return begin();
	}

	auto cend() const -> const_iterator {
		return end();
	}

	// reverse iterators all come for free as well
	auto rbegin() -> reverse_iterator {
		return reverse_iterator{ end() };
	}
	
	auto rend() -> reverse_iterator {
		return reverse_iterator{ begin() };
	}
	
	auto rbegin() const -> const_reverse_iterator {
		return const_reverse_iterator{ end() };
	}
	
	auto rend() const -> const_reverse_iterator {
		return const_reverse_iterator{ begin() };
	}
	
	auto crbegin() const -> const_reverse_iterator {
		return rbegin();
	}
	
	auto crend() const -> const_reverse_iterator {
		return rend();
	}

private:
    const ivec *lhs_;
    const ivec *rhs_;
    std::size_t len_;
};

#endif // COMP6771_ZIP_H
