#include "sort3.h"

#include <utility>

auto sort3(int &a, int &b, int &c) -> void {
	if (a > c) {
		std::swap(a, c);
	}

	if (b > c) {
		std::swap(b, c);
	}

	if (a > b) {
		std::swap(a, b);
	}
}

auto sort3(std::string &a, std::string &b, std::string &c) -> void {
	if (a > c) {
		std::swap(a, c);
	}

	if (b > c) {
		std::swap(b, c);
	}

	if (a > b) {
		std::swap(a, b);
	}
}
