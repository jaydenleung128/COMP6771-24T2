# Week 3 Exercises

## Q3.1. Plug-and-Play STL

There are many ready-made components in the STL that make common programming tasks extremely easy.
When it comes to using containers like `std::vector` and algorithms like `std::sort`, many useful things can be found in the `<functional>` header.

Your task is to complete the `sort_descending()` function in `src/3.1/sort_descending.cpp`.
You can find its documentation in `src/sort_descending.h`.

You also need to write at least **two** tests in `src/3.1/sort_descending.test.cpp` to make sure your code is correct!

## Q3.2. Vowel Sort

A powerful aspect of `std::sort` is being able to change the meaning of "sorted" by supplying a different comparator to the sort.

In olden times, this would be done by crafting a separate function each time and supplying a function pointer.
As of C++11, this is now all doable inline with `lambda` functions.

How might we use a lambda function to sort a vector of strings by the number of vowels in each string?
Furthermore, if the number of vowels are equal, then the strings should be lexicographically sorted.

In `src/3.2/vsort.cpp`, there is a stub for a function that accepts a vector of strings and sorts it in ascending order according to the above rules.

You need to implement this function using a lambda as the custom comparator.
You should also write at least **two** tests to verify that your code is correct.

## Q3.3. Statistically Marking

In `src/3.3/marks.txt` there is a newline separated file of anonymous marks from a previous offering of this course!
To show off your budding C++ prowess, you have decided to calculate the median, average, highest, and lowest mark from this newline-separated list using nothing but the C++ Standard Library. In particular:
- std::ifstream
- std::vector
- std::algorithms

In your enthusiasm, you decided to code your program in a modular style. So, in addition to a `calculate_stats()` function, you also made a separate function that loads in the marks from a file!

In reflection, you remembered your old Professor's words, and decided to write at least **two** tests overall to make sure your code is correct.

Both functions should be coded in `src/3.3/stats.cpp`, but more documentation is in `src/stats.h`. Your tests should be implemented in `src/3.3/stats.test.cpp`.

## Q3.4. Inverse Mappings

`std::map` is one of the Standard Library's most widely used types (owing mainly to the fact that the need for an associative array appears in many places).

One not-so-common but still vitally important operation on a map is to invert its keys and values.
For example,
```cpp
auto m = std::map<std::string, int>{{"hi", 42}, {"bob", 6771}};
```
the inversion of `m` would be
```cpp
auto n = std::map<int, std::string>{{42, "hi"}, {6771, "bob"}};
```

As you can see, the keys have been swapped with their values and vice-versa.

Your task is to implement the `invert()` operation for a map of `std::string` to `int`, namely `std::map<std::string, int>`.

However, rather than a simple inversion, there is an added constraint.

If, after inversion, the same key appears more than once (which can happen due to values having different keys in the original map), only the key/value pair with the longest string should ultimately be in the resulting map.
For example, for the map `m`,
```cpp
auto m = std::map<std::string, int> {
    {"a", 6771},
    {"ab", 6771},
    {"abc", 6771},
    {"xyz", 6772},
};
```
it's inversion should be:
```cpp
auto n = std::map<int, std::string> {
    {6771, "abc"},
    {6772, "xyz"},
};
```

In `src/3.4/invert.cpp`, implement the `invert` operation and in `src/3.4/invert.test.cpp`, write at least **three** tests to ensure your code is correct!

## Q3.5. Microbenchmarking Lookup

The various containers in the C++ Standard Library have different performance characteristics for different operations. For example, linear search in `std::vector` is presumed to be faster than in `std::list`, but potentially slower than in a `std::deque`.

In this activity, we will put these assumptions to the test with a microbenchmark!

In `src/3.5/microbenchmark.h`, there is documentation for a function that is to run a microbenchmark for a list, deque, and vector simultaneously. This function should return a `timings` structure, which is also in the provided header file.

Complete this function in `src/3.5/microbenchmark.cpp`. We have provided a random-number generator in there for you to use.

When you are done, you should also write at least **one** test in `src/microbenchmark.test.cpp`. You may wish to use the test as a way to verify/test your assumption about which container is the fastest for linear lookup...

Though not mandatory, you may also want to write a small program that uses your benchmarking code and does experiments to see under what conditions which container is faster. If you do so, it may help to consider these questions:
- What design and implementation trade-offs have been made between the various sequential containers?
- Has the programming-paradigm (i.e. OOP) of these datastructures made a difference?
- Has modern hardware been fully taken advantage of?

Feel free to discuss your answers to these questions with your tutor.

Hint: a useful library that deals with all things related to time (and dates!) is [`std::chrono`](https://en.cppreference.com/w/cpp/chrono).


## Q3.6. Reversal

Consider the following code:
```cpp
#include <iostream>
#include <vector>

int main() {
	std::vector<int> temperatures = {32, 34, 33, 28, 35, 28, 34};

	for (int i = 0; i < temperatures.size(); ++i) { // (*)
		std::cout << temperatures.at(i) << " ";
	}
	std::cout << "\n";

	for (const auto &temp : temperatures) {         // (^)
		std::cout << temp << " ";
	}
	std::cout << "\n";

	for (auto iter = temperatures.cbegin(); iter != temperatures.cend(); ++iter) { // (&)
		std::cout << *iter << " ";
	}
	std::cout << "\n";
}
```

Answer the following questions:

1. Why is the for-loop marked with an (*) potentially more unsafe than the others?
- a) It is a C-style for-loop, and the index could overflow.
- b) It is a C-style for-loop, and the comparison of signed vs. unsigned integers can produce surprising results.
- c) It is a C-style for-loop, and this makes it inherently inferior to C++ style for-loops.
- d) It is a C-style for-loop, and it is possible we go off the end of the `temperatures` vector.

2. We want to iterate through `temperatures` in reverse. Which loop in this code is easiest to change and why?
- a) (*): Index calculations are easy to do and most people are used to seeing index-based reverse iteration
- b) (^): range for-loops and an appropriate use of std::reverse conveys our intent the best.
- c) (^): all standard library containers provide reverse iterators.
- d) (&): just change the `cbegin` and `cend` to `rbegin` and `rend`.

3. What differences, if any, are there between `temperatures.begin()` and `temperatures.rend()`?
- a) An end-iterator, whether from `end()` or `rend()` is "one-past-the-end", and so is never dereferenceable, unlike `begin()`.
- b) No difference: `begin()` == `rend()` since the beginning of a range is the end of its reversal.
- c) The only difference is the type: `begin()` returns an `iterator` whereas `rend()` returns `reverse_iterator`. Everything else is the same.
- d) `rend()` would only compare equal to `begin()` if `temperatures` was empty.

## Q3.7. Categorising Iterators

Answer the following questions:

1. Consider this code:
```cpp
#include <vector>
int main() {
    const std::vector<int> v;
    auto iter = v.begin();
}
```
What iterator type and category is `iter`?
- a) constant iterator / random-access
- b) `const_iterator` / contiguous
- c) constant `const_iterator` / contiguous
- d) won't compile



2. Consider this code:
```cpp
#include <vector>
int main() {
    const std::vector<int> v;
    auto iter = v.cbegin();
}
```
What iterator type and category is `iter`?
- a) `const_iterator` / contiguous
- b) constant `const_iterator` / contiguous
- c) constant iterator / contiguous
- d) won't compile



3. Consider this code:
```cpp
#include <vector>
int main() {
    const std::vector<int> v;
    auto iter = (*v.begin())++;
}
```
What iterator type and category is `iter`?
- a) `const_iterator` / contiguous
- b) constant iterator / contiguous
- c) constant `const_iterator` / contiguous
- d) won't compile



4. Consider this code:
```cpp
#include <list>
int main() {
    std::list<int> li;
    auto iter = li.cbegin();
}
```
What iterator type and category is `iter`?
- a) constant iterator / bi-directional
- b) iterator / forward
- c) `const_iterator` / bi-directional
- d) won't compile



5. Consider this code:
```cpp
#include <forward_list>
int main() {
    std::forward_list<int> forward_li;
    auto iter = forward_li.cbegin();
}
```
What iterator type and category is `iter`?
- a) `const_iterator` / forward
- b) constant iterator / forward
- c) iterator / bidirectional
- d) won't compile



6. Consider this code:
```cpp
#include <forward_list>
int main() {
    const std::forward_list<int> forward_li;
    auto iter = (*forward_li.begin())++;
}
```
What iterator type and category is `iter`?
- a) `const_iterator` / forward
- b) iterator / forward
- c) `iter` is an `int`
- d) won't compile



7. Consider this code:
```cpp
#include <set>
int main() {
    std::set<int> st;
    const auto iter = st.begin();
}
```
What iterator type and category is `iter`?
- a) constant iterator / bidirectional
- b) iterator / forward
- c) iterator / bi-directional
- d) won't compile



8. Consider this code:
```cpp
#include <string>
int main() {
    std::string s;
    auto iter = s.begin();
}
```
What iterator type and category is `iter`?
- a) iterator / forward
- b) iterator / contiguous
- c) iterator / random-access
- d) won't compile



9. Consider this code:
```cpp
#include <iterator>
#include <iostream>
int main() {
    auto iter = std::istream_iterator<int>(std::cin);
}
```
What iterator type and category is `iter`?
- a) `const_iterator` / input
- b) iterator / input
- c) iterator / forward
- d) won't compile



10. Consider this code:
```cpp
#include <iterator>
#include <iostream>
int main() {
    auto iter = std::ostream_iterator<int>(std::cout, " ");
}
```
What iterator type and category is `iter`?
- a) iterator / output
- b) `const_iterator` / output
- c) constant iterator / input
- d) won't compile

## Q3.8. Algorithms Galore

Answer the following quetsions:

1. Consider the code below:
```cpp
auto first(const std::vector<int> &v, const int needle) {
  for (auto i = v.begin(); i != v.end(); ++i) {
    if (*i == needle) {
      return i;
    }
  }
  return v.end();
}
```
What standard algorithm can this code be replaced by?
- a) std::get
- b) std::find_if
- c) std::search
- d) std::find

2. Consider the code below:
```cpp
auto second(std::vector<int> &v, std::vector<int>::iterator new_first) {
  auto copy = std::vector<int>(v.begin(), new_first);
  v.erase(v.begin(), new_first);
  return v.insert(v.end(), copy.begin(), copy.end());
}
```
What standard algorithm can this be replaced by?
- a) std::erase
- b) std::shift_left
- c) std::rotate
- d) std::shift_right

3. Consider the code below
```cpp
auto third(std::span<float> floats) {
  auto v = std::vector<float>{};
  for (auto f : floats) {
    v.push_back(f);
  }

  auto m = std::numeric_limits<float>::max();
  for (auto f : v) {
    if (f < m) m = f;
  }

  auto M = std::numeric_limits<float>::min();
  for (auto f : v) {
    if (M < f) M = f;
  }

  return std::make_pair(m, M);
}
```
What sequence of standard algorithms can this reasonably be replaced by?
- a) std::copy -> std::min_element -> std::max_element
- b) std::copy -> std::minmax_element
- c) std::vector iterator constructor -> std::min_element -> std::max_element
- d) std::memcpy -> std::max_element -> std::min_element
