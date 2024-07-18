#ifndef COMP6771_ROPE_H
#define COMP6771_ROPE_H

#include <string>
#include <vector>
#include <utility>

class rope {
	class iter {
	public:
		using iterator_category = std::bidirectional_iterator_tag;
		using value_type = char;
		using reference = const value_type&;
		using pointer = void;
		using difference_type = std::ptrdiff_t;

		iter() = default;

		auto operator++() -> iter& {
			++inner_;  // go to the next char
			// if hit the end of this string, and aren't at the end of the rope
			while (outer_ != last_ and inner_ == outer_->end()) {
				// go to the next string
				++outer_;
				if (outer_ != last_) {
					// and look at the start of it
					inner_ = outer_->begin();
				}
			}
			return *this;
		}

		auto operator--() -> iter& {
			// gotta do it the other way around, now
			// if we're at the end, step back until we find a non-empty string
			// (don't need to handle if they don't exist,
			//  since if so `--r.end()` doesn't make sense anyway)
			while (outer_ == last_ or inner_ == outer_->begin()) {
				--outer_;
				inner_ = outer_->end();
			}
			--inner_;
			return *this;
		}

		// postfix is always a simple formula
		auto operator++(int) -> iter {
			auto old = *this;
			++*this;
			return old;
		}

		auto operator--(int) -> iter {
			auto old = *this;
			--*this;
			return old;
		}

		auto operator*() const -> reference {
			return *inner_;
		}

		friend auto operator==(const iter& lhs, const iter& rhs) -> bool {
			// make sure the "outer" is the same; if so,
			return lhs.outer_ == rhs.outer_ and
			// either we're at the end of the rope, or we're pointing at the same char
				(lhs.outer_ == lhs.last_ or lhs.inner_ == rhs.inner_);
		}

	private:
		using outer_t = std::vector<std::string>::const_iterator;
		using inner_t = std::string::const_iterator;

		iter(outer_t first, outer_t last)
			: last_(last)
			, outer_(std::find_if_not(first, last, [](const auto &s) { return s.empty(); }))
			, inner_(outer_ == last_ ? inner_t{} : outer_->begin())
		{}

		outer_t last_ {};	// the end of the rope
		outer_t outer_ {};	// which string we're looking at
		inner_t inner_ {};	// which character we're looking at in the string

		friend class rope;
	};

public:
	// iterator types
	using iterator = iter;
	using const_iterator = iter;
	using reverse_iterator = std::reverse_iterator<iterator>;
	using const_reverse_iterator = std::reverse_iterator<const_iterator>;

	explicit rope(std::vector<std::string> rope) : rope_{std::move(rope)} {}

	// non-const begin/end
	auto begin() -> iterator {
		return { rope_.begin(), rope_.end() };
	}
	
	auto end() -> iterator {
		return { rope_.end(), rope_.end() };
	}

	// const begin/end; get cbegin/cend for free
	auto begin() const -> const_iterator {
		return { rope_.begin(), rope_.end() };
	}

	auto end() const -> const_iterator {
		return { rope_.end(), rope_.end() };
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
	std::vector<std::string> rope_;
};

#endif // COMP6771_ROPE_H
