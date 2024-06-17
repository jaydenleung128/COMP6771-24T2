#ifndef COMP6771_VSORT_H
#define COMP6771_VSORT_H

#include <string>
#include <vector>

/*
 * Sorts `vs` in ascending order according to the number of vowels in the string
 * If two strings have the same number of vowels, then sort lexicographically (in ascending order)
 *
 * Can assume that only lowercase alphabetical characters will be used.
 */
auto vsort(std::vector<std::string>& vs) -> void;

#endif // COMP6771_VSORT_H