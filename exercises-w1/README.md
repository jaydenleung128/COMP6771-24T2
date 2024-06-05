# Week 1 Exercises

## Q1.1. Introduction using a set diff

In `src/1.1/setdiff.h` there is a documentation for a function that removes elements in one vector from another. In the provided test stub in `src/1.1/setdiff.test.cpp`, write **three** or more _unit tests_ for this function. Considerations include:
- a test for invalid input
- a test for an _edge_ case
- a test for the average use case

When you are happy with the tests, implement the function in `src/setdiff.cpp` so that your tests pass.

## Q1.2. Using and Testing `std::vector`

One of the most widely used containers from the C++ Standard Library is `std::vector`. A vector is a dynamic array that looks after its own memory and allows elements to be inserted, retrieved, compared for equality, etc.

Alot can be done with a vector and the purpose of this exercise is to gain familiarity with its various operations (called _member functions_ or _methods_).

In `src/1.2/fib_vector.cpp`, there is an incomplete implementation of a function that calculates all of the [Fibonacci numbers](https://en.wikipedia.org/wiki/Fibonacci_number) and returns them in a `std::vector<int>` as well as a few failing tests. Write a proper implementation of `fibonacci()` and more tests so that you more become familiar and confident with using a vector (and also with testing!).

Hint: some of the most widely used methods on vectors are:
- `push_back(elem)`: adds an elements to the vector at the end
- `size()`: returns how many elements are currently in the vector
- `empty()`: returns true if and only if `size() == 0` (**N.B.** this does not `clear()` the vector!)
- `at(n)`: get the nth element from the vector. Can also use `[]`.

A full description of these methods can be found [here](https://en.cppreference.com/w/cpp/container/vector).

## Q1.3. Evolution: C to C++

Write a C++ program in `src/1.3/cat.cpp` that mimics the C program written below.
The program is intended to mimic the behaviour of the UNIX command `cat`.
For each C++ change, think about what advantages C++ provides.

Make sure you check with your tutor that your C++ code is styled according to modern guidelines.

```c
#include <stdio.h>

int main() {
  char buffer[100];
  fgets(buffer, 100, stdin);
  printf("%s", buffer);
  return 0;
}
```

## Q1.4. Gotta Sort It Out

Write a function, called `sort3` in `src/1.4/sort3.cpp`, which takes three `int` references and sorts them in ascending order.

Then, write **two** test cases in `src/1.4/sort3.test.cpp` to confirm that `sort3` is correct.

You should then write an overload for `sort3` so that it also sorts three `std::string` references. Don't forget to write at least **two** more test cases!

## Q1.5. Catch2 Syntax

Answer the following questions:

1. What is a `TEST_CASE`?
- a) A `TEST_CASE` is a uniquely-named testing scope that must contain every test we write about our program.
- b) A `TEST_CASE` is a fancy macro that has no effect in "real" code.
- c) A `TEST_CASE` is a uniquely-named testing scope that will keep track of all the `CHECK`s and `REQUIRE`s that pass or fail.
- d) A `TEST_CASE` is a macro where only compile-time evaluable assertions about our code can be written.


2. What is a `CHECK`? In what way, if any, is it different to `assert()`?
- a) `CHECK` and `assert` are both macros and do the exact same thing.
- b) `CHECK` and `assert` are both macros, but a `CHECK` will evaluate an expression and report it if it's false whereas `assert` will crash the program.
- c) `CHECK` is a function that suggests a fact about our code should be true, but `assert` enforces it.
- d) `CHECK` records the failure of an assertion but does nothing about it and is entirely unrelated to `assert`.

3. What is a `REQUIRE`? In what way, if any, is it different to `assert()`?
- a) `REQUIRE` evaluates an expression and crashes the program if it is false but `assert` will report it to the user.
- b) `REQUIRE` and `assert` both evaluate expressions and terminate the currently executing test if false.
- c) `assert` and `REQUIRE` both evaluate expressions, but only `assert` has an effect if the expression is false.
- d) `REQUIRE` evalutes an expression and if false will terminate the currently executing test and move onto the next one. It is entirely unrelated to `assert`.

4. What are `SECTION` blocks in Catch2?
- a) `SECTION` blocks are ways to divide testing logic in `TEST_CASE`s. Any state changes in a `SECTION` are not reflected in `SECTION`s at the same level.
- b) `SECTION` blocks are a way to break up long tests and have little use other than that.
- c) `SECTION`s are unique testing scopes that can only contain `TEST_CASE`s.
- d) `SECTION`s are part of Behaviour Driven Development and group together `SCENARIO`s.

5. What goes between the parentheses in `TEST_CASE`s and `SECTION`s?
- a) The function or class name that is currently being tested.
- b) A succinct and insightful description in plain language of the code under test.
- c) A description that matches a similarly-worded comment directly above the `TEST_CASE`/`SECTION`.
- d) A note for future readers of your code about what you were thinking at the time of writing this test.

## Q1.6. Constant Referencing

Answer the following questions:

1. Are there any errors in this code and if so what are they?
```cpp
auto i = 3;
i = 4;
```
- a) Yes: `auto` is a reserved keyword
- b) Yes: it is illegal to initialise a variable after it is defined.
- c) Maybe: it depends on what CPU this code is run on.
- d) No: assignment after initialisation is legal, even in C.

2. Are there any errors in this code and if so what are they?
```cpp
const auto j = 5;
--j;
```
- a) Yes: `j` is a constant integer which cannot be modified.
- b) Maybe: it depends if the programmer prefers east or west const.
- c) No: decrementing a constant integer creates a new one.
- d) Yes: `auto` and `const` should not be mixed.

3. Are there any errors in this code and if so what are they?
```cpp
auto age = 18;
auto& my_age = age;
++my_age;
```
- a) Maybe: it depends if the code is compiled as C++98 or C++11 or higher.
- b) No: my_age is a reference to age, so preincrement is perfectly legal.
- c) Yes: references are inherently const and so modifying `age` through `my_age` is illegal.
- d) No: `my_age` is a copy of `age` and modifying `my_age` has no impact on `age` whatsoever.

4. Are there any errors in this code and if so what are they?
```cpp
auto age = 21;
const auto &my_age = age;
--my_age;
```
- a) Yes: `auto` references can only be used with explicit type annotations.
- b) Maybe: if this code is compiled with the "-pedantic" flag in GCC, it would be perfectly legal.
- c) No: my_age is a const reference, but `age` is not constant, so this is fine.
- d) Yes: `my_age` is a reference to a constant integer, which cannot be modified.
