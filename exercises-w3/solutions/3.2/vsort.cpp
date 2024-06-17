#include "vsort.h"

auto vsort(std::vector<std::string> &vs) -> void {
  std::sort(vs.begin(), vs.end(), [](const std::string &x, const std::string &y) {
	const auto vowels = [] (char c) {
		return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
	};

    auto xcount = std::count_if(x.cbegin(), x.cend(), vowels);
    auto ycount = std::count_if(y.cbegin(), y.cend(), vowels);
	
	return xcount == ycount ? x < y : xcount < ycount;
  });
}
