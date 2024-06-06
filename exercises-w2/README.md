# Week 2 Exercises

## Q2.1. Definitive Declarations

Answer the following questions

1. Is the line marked (*) a declaration or a definition?
```cpp
int get_age(); // (*)

int main() {

}
```
- a) Declaration
- b) Definition
- c) Neither
- d) Both

2. Is the line marked (*) a declaration or a definiton?
```cpp
int get_age();

int age = get_age(); // (*)
```
- a) Declaration
- b) Definition
- c) Neither
- d) Both

3. Is the line marked (*) a declaration or a definition?
```cpp
int main() {
  auto age = 20; // (*)
}
```
- a) Declaration
- b) Definition
- c) Neither
- d) Both

4. Is the line marked (*) a declaration or a definition?
```cpp
int main() {
  auto age = 20;
  std::cout << age << std::endl; // (*)
}

```
- a) Declaration
- b) Definition
- c) Neither
- d) Both

5. Is the line marked (*) a declaration or a definition?
```cpp
int get_age();

int get_age() { // (*)
  return 6771;
}
```
- a) Declaration
- b) Definition
- c) Neither
- d) Both

## Q2.2. Resolution Overload

Answer the following questions

1. Consider the code below:
```cpp
/* 1 */ auto put(char) -> void;
/* 2 */ auto put(int) -> void;
/* 3 */ auto put(const char) -> void;
/* 4 */ auto put(char &) -> void;

put('a');
```
Which overload of `put` would be selected and why?
- a) Overload 1: `put` was called with a `char` and overload 3 is just a redeclaration of overload 1.
- b) Overload 2: `char` is implicitly promotable to `int` and so overload 2 is the best match.
- c) Overload 3: `put` was called with a temporary `const char`.
- d) Overload 4: `put` was called with a temporary `char` and temporaries preferentially bind to references.


2. Consider the code below:
```cpp
/* 1 */ auto put(char) -> void;
/* 2 */ auto put(char &) -> void;
/* 3 */ auto put(const char &) -> void;
char c = 'a';
put(c);
```
Which overload of `put` would be selected and why?
- a) Overload 1: `put` was called with a `char`.
- b) Overload 2: `put` was called with a mutable `char` and and references have higher priority.
- c) Overload 3: `put` was called with a const `char` and const references have higher priority.
- d) No overload: this call is ambiguous.


3. Consider the code below:
```cpp
/* 1 */ auto memcpy(char *dst, const char *src, int n = 0) -> void *;
/* 2 */ auto memcpy(const char *dst, char * const src) -> char *;

char *dst = /* appropriate initialisation... */;
const char *src = /* appropriate initialisation... */;

void *ptr = memcpy(dst, src);
```
Which overload of `memcpy` would be selected and why?
- a) Overload 1: both overloads are equally viable but the return type of overload 1 matches `ptr`'s type better
- b) Overload 2: has exactly two arguments and a non-bottom-level const pointer is always convertible to a bottom-level const pointer.
- c) Overload 1: the first two arguments match perfectly and the default argument is used for the third.
- d) Overload 2: the top-level const `src` argument has higher priority than the corresponding bottom-level const `src` in overload 1.


4. Consider the code below
```cpp
/* 1 */ auto min(int(&arr)[2]) -> int;
/* 2 */ auto min(int *arr) -> int;
/* 3 */ auto min(int(&arr)[]) -> int;

auto fn(int buf[3]) -> void {
    min(buf);
}
```
Which overload of `min` would be selected and why?
- a) Overload 1: though `min` was called with an array of length 3, 3 is close to 2, so this is the best match.
- b) Overload 2: the `buf` argument decays to `int *` and so overload 2 is the best match.
- c) Overload 3: neither `int(&)[2]` nor `int *` match `int(&)[3]` perfectly but a reference to an array of unknown length does, so this is the best match.
- d) No Overload: this call is ambigous.


5. Consider the code below:
```cpp
/* 1 */ auto sink(int i, ...);
/* 2 */ auto sink(int i, short s);
/* 3 */ auto sink(...);

auto L = std::numeric_limits<long>::max();
sink(1, L);
```
Which overload of `sink` would be selected and why?
- a) Overload 1: correct number of parameters and a variadic function is preferred over a narrowing conversion from `long` to `short`
- b) Overload 2: correct number of parameters and variadic functions have the lowest priority in overload resolution, so this is the only viable candidate.
- c) Overload 3: by definition, a single-parameter variadic function can be called with any number and type of arguments, so it is always the best match.
- d) No Overload: this call is ambigous.

## Q2.3. Programmable Errors

Answer the following questions

1. What kind of error is first displayed in the below code?
```cpp
// api.h
int rand();

// me.cpp
#include "api.h"
int rand() {
    return 42;
}

// you.cpp
int rand() {
    return 6771;
}

// client.cpp
#include "api.h"
int i = rand();
```
- a) Compile-time error: `you.cpp` did not include `api.h`
- b) Compile-time error: multiple definitions of `rand()`.
- c) Link-time error: multiple definitions of `rand()`.
- d) Logic Error: 6771 is not a random number!

2. What kind of error is first displayed in the below code?
```cpp
namespace constants {
  #define N 6771  
}

int N = constants::N;

int main() {
    int ints[N] = {1, 2, 3};
}
```
- a) Logic error: `constants` is a bad name for a namespace
- b) Compile-time error: macros do not obey namespace rules and so `int N` is changed to `int 6771`.
- c) run-time error: main does not return a value.
- d) Compile-time error: `N` is not const and so cannot be used in `ints[N]`.

3. What kind of error is displayed in the below code?
```cpp
#include <vector>

int main() {
    std::vector<int> v;
    unsigned i;
    while (i-- > 0) {
        v.push_back(i);
    }
}
```
- a) Link-time error: `i` is just a variable declaration and the real `i` hasn't been defined yet.
- b) Logic error: `i` is uninitialised and so its use is illegal.
- c) Logic error: `v` is not used after the for-loop.
- d) Run-time error: pushing back continuously to a vector can result in an "out of memory" error

4. What kind of error is displayed in the below code?
```cpp
int main() {
    int *ptr = new int{42};

    *ptr = 6771;

    return *ptr;
}
```
- a) Logic-error: you are only allowed to return numbers in the range [-128, 128] from `main()`.
- b) Runtime-error: `new` can fail allocation and throws an exception if that happens
- c) Compile-time error: `int{42}` is invalid syntax.
- d) Logic-error: programmer did not check if `ptr` was `nullptr` or not before dereferencing.

## 2.4. Type-Safe Scaling

C++ has a poignant emphasis on strong type-safety. To that end it offers a type-safe version of the C-style cast called `static_cast` which only allows conversion between compatible types e.g. `int` to `float`, `void *` to `int *` etc., and will not allow unrelated casts e.g. `void *` to `int`.

In this exercise we will use `static_cast` to safely scale a vector of integers by a `double` value and return a new vector of doubles.

In `src/2.4/scale.h` there is documentation for `scale()` which does this conversion.
Implement this function in `src/2.4/scale.cpp`.
You will also need to write at least **two** tests for it in `src/2.4/scale.test.cpp`.

To improve ease of use, also add a _default value_ of 0.5 for the scaling factor.
This will allow users to not have to pass a scale factor when commonly scaling a vector in half.

## 2.5. Finding a Mismatch

The **S**tandard **T**emplate **L**ibrary (aka the STL, now part of the C++ standard proper) has three fundamental concepts: containers, iterators, and algorithms. Iterators are the glue that sits between containers of data and the algorithms that operate on them. By using these three concepts together, code reuse is maximised and composition of existing code becomes very easy.

In this exercise you will be using `std::vector<int>::iterator` to implement a less general version of [std::mismatch](https://en.cppreference.com/w/cpp/algorithm/mismatch), one of the many algorithms provided by the standard library.

There is documentation for our version of `mismatch()` in `src/2.5/mismatch.cpp`. Complete this function and write at least **three** more tests to verify your code is correct. Two have already been provided for you.

## 2.6. Is It a Perumutation?

The purpose of this exercise is to get experience using different parts of the C++ Standard Library's helpful types and data structures.
In src/permutation.h, there is documentation for a function that, given two strings, determines if one string is a permutation of the other. In this instance, a string s1 is a permuation of another string s2 if:
 * s1 and s2 contain the same number of letters
 * s2 contains all of the letters of s1, but not necessarily in the same order.
The empty string is a permutation of itself.

You need to implement this function in `src/2.6/permutation.cpp` and write at least two tests in `src/2.6/permutation.test.cpp`.

## 2.7. Sorting Sequences

The C++ Standard Library provides many [algorithms](https://en.cppreference.com/w/cpp/header/algorithm), one very widely-used one being [std::sort](https://en.cppreference.com/w/cpp/algorithm/sort). `std::sort` accepts two iterators denoting a range and performs an optimised sort on that range.

In this exercise, we shall explore what requirements `std::sort` expects this pair of iterators to satisfy and how the [sequence containers](https://en.cppreference.com/w/cpp/container) `std::vector`, `std::list`, and `std::array` satisfy these requirements.

In `src/2.7/assortment.cpp` there are 3 overloads for a function `sort()` which accepts a vector, array, and list of integers. There are also three test cases in `src/2.7/assortment.test.cpp` for sanity checking.
Try implementing each `sort()` function using `std::sort`.

You may notice that the program will not compile.

Consider these questions:
- Where in the code is the compilation error happening?
- **Why** is this compilation error happening? (hint: the compiler error may only be a symptom, not the cause!)
- How might one resolve this error? (Hint: `std::vector` is always handy...)

Modify your implementation such that now the tests pass.

## 2.8. Mixing Paint

C++ builds upon many constructs found in C. For example:
- `std::function` (and more) over raw function pointers
- `enum class` over `enum`
- `std::optional` over "magic" invalid values such as `nullptr` for an absent `T*`

In this exercise we shall implement a paint-mixing algorithm to gain familiarity with these new constructs. Namely:
- Paints will be represented by an `enum class` called `paint`.
- `sizeof(<any paint>) == 1`.
- The paint colours should be:
    - red
    - green
    - blue
    - yellow
    - cyan
    - magenta
    - brown
- Instead of baking-in which mixing strategy to use, we shall encapsulate it with a `std::function`.
- If a combination of colours doesn't exist, we will denote its absence by a `std::optional`.

In `src/2.8/mixing_paint.h`, there is documentation for a function `mix` that accepts a mixing strategy and vector of paints and mixes them according to the given strategy.
Mixing follows the left-fold algorithm, for example, if we were summing integers...:
```cpp
auto add(int x, int y) -> int { return x + y; }

auto sum(const std::vector<int> nums, int init) -> int {
    for (auto i : nums) {
        init = add(init, i);
    }

    return init;
}
```
Here, the accumulator is on the left of the `add()` function and the next element in the list is on the right.

There is also documentation for a default mixing strategy `wacky_colour` which you will also need to implement.

Complete these functions in `src/2.8/mixer.cpp` and write at least **two tests** for `mixer` and **two tests** for `wacky_colour` in `src/2.8/mixer.test.cpp`.
