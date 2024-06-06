#include "permutation.h"

#include <unordered_map>

auto count_letters(std::string const& x) -> std::unordered_map<char, int> {
	auto dictionary = std::unordered_map<char, int>();

	for (const auto letter : x) {
		auto result = dictionary.find(letter);
		if (result == dictionary.cend()) {
			dictionary.emplace(letter, 1);
			continue;
		}
		++result->second;
	}

	return dictionary;
}

auto is_permutation(const std::string &x, const std::string &y) -> bool {
	return count_letters(x) == count_letters(y);
}

