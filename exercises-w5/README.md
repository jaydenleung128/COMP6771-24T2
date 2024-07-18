# Week 5 Exercises

## Q5.1. Overloaded Operators

Write the alternative which most accurately answers the questions below. 

For the following questions, consider the below class:
```cpp
class vec3 {
public:
    auto operator[](int n) { return elems_[n]; }

    friend auto operator>>(std::istream &is, vec3 &v) -> std::istream&;

private:
    double elems_[3] = {0, 0, 0};
}
```

1. In what cases would one need to overload an operator for a const and non-const version?
- a) Always; it is impossible to know how your code will be used in the future.
- b) Only when the operator is a member function and not a non-member function.
- c) When the operator has both a "getter" and "setter" version the two overloads are necessary.
- d) You should only add a const version if the return type is a reference type.

2. What could be the return type of `vec3::operator[]` as it is currently written?
- a) `double *`
- b) `double &`
- c) `volatile double`
- d) `double[]`

3. Is the `vec3` class currently const-correct? If not, how would you change it to be so?
- a) Not const-correct: `operator[]()` needs a const version so const-objects can still be indexed into. The returned value must not be modifiable, however.
- b) const-correct: `elems_` is not const, so this class can never have const-qualified methods.
- c) Not const-correct: the `int n` parameter in `operator[]()` is not bottom-level const-qualified.
- d) const-correct: `auto` correctly deduces the right const-correct type depending on if `this` is a const-object or not.

4. Given the serialised format for a `vec3` is `double1 double2 double3`, what could be a _potential_ implementation for `operator>>` and why?
```cpp
// a
// fill the 3 elems of v via a standard algorithm.
// no need to return "is" for chaining (due to the serialised format of vec3)
auto operator>>(std::istream &is, vec3 &v) -> std::istream& {
    std::copy(std::istream_iterator<double>{is}, std::istream_iterator<double>{}, v.elems_, v.elems_ + 3);
}

// b
// fill the 3 elems of v.
// return "is" for chaining.
auto operator>>(std::istream &is, vec3 v) -> std::istream& {
    is >> v.elems_[0];
    is >> v.elems_[1];
    is >> v.elems_[2];
    return is;
}

// c
// fill the 3 elements of v from is.
// return "is" for chaining.
auto operator>>(std::istream &is, vec3 &v) -> std::istream& {
    is >> v.elems_[1];
    is >> v.elems_[2];
    is >> v.elems_[3];
    return is;
}

// d
// fill the 3 elems of v via a standard algorithm.
// return "is" for chaining.
auto operator>>(std::istream &is, vec3 &v) -> std::istream& {
    std::copy(std::istream_iterator<double>{is}, std::istream_iterator<double>{}, v.elems_);
    return is;
}
```

5. Is friendship necessary for `vec3`'s `operator>>` overload? Why or why not?
- a) Necessary: every implementation must use `elems_`, which is private -- can only access this via friendship.
- b) Necessary: non-member operator overloads should always be hidden friends.
- c) Not necessary: `operator>>` could potentially use `vec3::operator[]()` (which is public) to fill the vec3's elements, so defining it as a friend is superfluous.
- d) Not necessary: `operator>>` can be implemented as a member function, and we only ever use it like so: `my_vec3 >> std::cin`

## Q5.2. Questionable Overloads

Write the alternative which most accurately answers the questions below. 

1. Consider the following class:
```cpp
class vec3 {
public:
  vec& operator+=(const vec &p);
  vec& operator-=(const vec &p);

  vec& operator*=(const vec &p);

private:
  int x_;
  int y_;
  int z_;
};
```
Why would this be considered not a very wise decision to provide an overload for `operator*=`?
- a) The semantic of multiplying two vectors together does not exist.
- b) `operator*=` should be replaced with `operator/=`, which makes more mathematical sense.
- c) `operator*=` obscures the actual logic of the operation and can potentially obfuscate code.
- d) The semantic of multiplying two vectors together is ambiguous. Dot or Cross product?

2. Consider the following class:
```cpp
class i32 {
public:
  friend i32 operator&&(const i32 &, const i32 &);
  friend i32 operator||(const i32 &, const i32 &);

private:
  std::int32_t i_;
}
```
Could this be considered to be a valid use of operator overloading? Why or why not?
- a) Valid: we are boxing a native 32-bit integer to work like a built-in `int`, where && and || are well-defined.
- b) Invalid: logical-AND and logical-OR are defined on booleans, not integers (of any size).
- c) Valid: for two `int`s `i1` and `i2`, `i1` && `i2` produces a reasonable result.
- d) Invalid: as written, these overloads only work with `i32`, but it is possible to AND and OR together other types with `i32` too, such as booleans. The overloads should accept a more general type.

## Q5.3. Iterator Invalidation

Write the alternative which most accurately answers the questions below.

1. Consider the following code:
```cpp
auto s = std::unordered_set<int>{1, 2, 3};
auto iter = s.find(1);

s.insert(4);

std::cout << *iter << std::endl;
```
Has iterator invalidation happened here, and if so, why?
- a) Yes: inserting into an array-based container always causes iterator invalidation.
- b) No: `std::unordered_set` always keeps its array length as a prime number and, since the next biggest prime after 3 is 7, there is enough space to insert a new element without a rehash.
- c) Possible: if the internal load factor has been exceeded and the elements had to be copied and rehashed into a new array, then all iterators are invalidated.
- d) Yes: `std::unordered_set` always keeps its array length as a prime number and, since the capacity before inserting is equal to the number of elements, it is guaranteed there will be a new array allocation and rehash, invalidating all iterators.

<br />

2. Consider the following code:
```cpp
auto v = std::vector{};
v.reserve(2);
for (auto i = 0; i < 2; ++i) {
    v.push_back(i);
}
auto iter = v.begin();
v.push_back(3);

std::cout << *iter << std::endl;
```
Has iterator invalidation happened here, and if so, why?
- a) Possible: if the capacity of `v` hasn't been reached yet, then there will be no invalidation. Otherwise, there will be.
- b) Yes: we reserved two spaces and filled them all so, at the time of the next push back, a new array will be allocated and all elements moved over, which will invalidate iterators.
- c) No: We ensured there was enough space in the vector when we called `reserve()`.
- d) Possible: irrespective of calls to `reserve()`, almost all implementations of `std::vector` grow geometrically and keep at least twice as much space as they report to via `capacity()`. If the true internal capacity has been reached, then the iterators will be invalidated, otherwise they won't be.

<br />

3. Consider the following code:
```cpp
auto v = std::vector{3, 2, 1};
auto iter = v.begin();
while (iter != v.end() - 1) {
    iter = v.erase(std::find(v.begin(), v.end(), *iter));
}

std::cout << *iter << std::endl;
```
Has iterator invalidation happened here, and if so, why?
- a) No: whilst modifying a vector we're looping over usually is disastrous, we are reassigning the loop variable `iter` every time to ensure it remains valid.
- b) Yes: you should never modify vectors when you loop over them.
- c) Yes: because an iterator separate to `iter` is passed to `v.erase()`, it invalidates `iter`. If, however, we had written `iter = v.erase(iter);`, it would not be invalidated.
- d) Possible: implementors of `std::vector` are free to choose whether or not this specific use-case invalidates iterators, so it depends on which version of the standard library you compile with.


4. Consider the following code:
```cpp
auto s = std::set<int>{1, 2, 3};
auto iter = s.find(3);

s.erase(2);

std::cout << *iter << std::endl;
```
Has iterator invalidation happened here, and if so, why?
- a) No: erasing an unrelated element from a `std::set` has no effect on `iter`.
- b) Yes: `std::set`, as a binary search tree, always rebalances itself after every modification.
- c) Possible: `std::set`, as a red-black tree, may rebalance itself if the erased element is in the ancestry of `iter`.
- d) No: `std::set` only invalidates iterators when it is moved-from (i.e., in code like `auto s2 = std::move(s)`).

## Q5.4. Booked Out

Implement the below specification in `src/5.4/book.h` and/or `src/5.4/book.cpp`.

You should also should write at least **three** tests in `src/5.4/book.test.cpp`.

### Member Functions

```cpp
book(const std::string &name, const std::string &author, const std::string &isbn, double price);
```
Constructor.
- Accepts strings representing the name, author, and isbn of this book, and a double denoting the price.
- Should initialise private internal variables of corresponding type with these values.

<br />

```cpp
explicit operator std::string() const;
```
Explicit type conversion operator to `std::string`.
- Should convert `*this` to a string.
- Format is: `<author>, <name>`.

For example:
```cpp
book b = {"Tour of C++11", "Bjarne Stroustrup", "0123456789X", 9000}; // very valuable book
std::string s = static_cast<std::string>(b);
std::cout << s;
```
Output: `Bjarne Stroustrup, Tour of C++11`

<br />

```cpp
const std::string &name() const;
```
Returns the name of this book.

<br />

```cpp
const std::string &author() const;
```
Return the author of this book.

<br />

```cpp
const std::string &isbn() const;
```
Return the ISBN of this book.

<br />

```cpp
const double &price() const;
```
Return the price of this book.

### Non-member Functions
```cpp
bool operator==(const book &lhs, const book &rhs);
```
Equality operator overload.
- Compares two books for equality.
- Two books are equal if they have the same ISBN.

<br />

```cpp
bool operator!=(const book &lhs, const book &rhs);
```
Inequality operator overload.
- Compares two books for inequality.
- **Hint**: you may be able to reuse another piece of code here...

<br />

```cpp
bool operator<(const book &lhs, const book &rhs);
```
Less-than relation operator overload.
- Orders books according to ISBN.
- `lhs < rhs` iff `lhs.isbn < rhs.isbn`.

<br />

```cpp
std::ostream &operator<<(std::ostream &os, const book &b);
```
Output stream operator overload.
- Prints out `b`'s details to `os`.
- Should be in the format: `<name>, <author>, <isbn>, $<price>`
- Price, when printed, should be rounded to two decimal places.

For example:
```cpp
book b = {"Tour of C++11", "Bjarne Stroustrup", "0123456789X", 9001}; // extremely valuable book
std::cout << b;
```
Output: `Tour of C++11, Bjarne Stroustrup, 0123456789X, $9001.00`

## Q5.5. Value-centric C++ (2/2)

C++ has value semantics by default (rather than reference semantics like other languages, such as Java). Classes allow developers to write their own value-types that act, look, and feel like the regular built-in types like `int` or `double`.

In this exercise we will be extending the previous `rational_number` class to feel more like a built-in type by replacing some of its operations with operator overloads.

In `src/5.5/rational_oo.h` and/or `src/5.5/rational_oo.cpp`, modify the `rational_number` class by:
- Replacing the previous `add(), sub(), mul(), div()` friend functions with their respective overloaded operators. You should consider the signatures of the above functions when deciding which overloaded operator to replace them with.
- Replacing the previous `eq(), ne()` friend functions with their respective overloaded operators. You should consider the signatures of the above functions when deciding which overloaded operator to replace them with.
- Replacing the previous `value()` member function with a type conversion operator to get the value of the rational number as a `double`.
- Adding a new operator overload for `operator[]` that:
    - When passed `'^'`, returns the numerator.
    - When passed `'v'`, returns the denominator.
    - There should be both a getter and setter version of this operator.
    - You can assume this function will only ever be passed one of `'^'` or `'v'`

Modify your previous tests so that they now use the overloaded operators. This means you should have at least **three** tests.


## Q5.6. Ropeful

One way we could implement a "rope" class would be to have a vector of strings.

Of course, a rope is logically contiguous, whereas the elements of a vector are disjoint.

With the power of a custom iterator, however, we can bridge the discontinuities and realise our dreams of having a rope-like container in C++!

In `src/5.6/rope.h`, you will find the stubs of two classes, `rope`, and its iterator `rope::iter`.

Your task is to complete the `rope` class's implementation so that it models [a reversible container](https://en.cppreference.com/w/cpp/named_req/ReversibleContainer), and also to implement `rope::iter` so that it models [a bidirectional iterator](https://en.cppreference.com/w/cpp/named_req/BidirectionalIterator).

There is a client program in `src/5.6/rope_user.cpp` which will give hints as to how the `rope` class is intended to be used. You have successfully completed this activity when this program compiles and runs without error.

**Note**: You are not allowed to modify `src/5.6/rope_user.cpp`.

**Implementation Hints:**
- A contiguous view over a vector of strings implies that each "element" of the range is a single `char`.
- It should not be possible to modify the elements of the range through the iterator. Therefore, you only need to implement a `const_iterator`. The type `rope::iterator` should still be available, though.
- Where possible, it is always preferable to delegate to the Standard Library.
- Friendship will likely be necessary.



## Q5.7. zip++

With C++20 came a great number of additions (concepts, ranges, modules, etc.). Despite all of these benefits, C++20 _still_ doesn't have anything like Python's `zip()`*. `zip()` accepts two ranges and returns a range containing the pairs of corresponding elements, stopping when the shorter range is exhausted.
For example:
```cpp
std::vector<int> i1 = {1, 2, 3};
std::vector<int> i2 = {4, 5};

// Dereferencing the iterator from zip returns a std::pair<int, int>
for (const std::pair<int, int> &p : zip{i1, i2}) {
    std::cout << p.first << " " << p.second << std::endl;
}

Outputs:
1 4
2 5
```

In this activity we shall build up a new `zip` type in `src/5.7/zip.h` and/or `src/5.7/zip.cpp`, and finally have access to something Python has had access to for _years_.

With the `zip` type comes its iterator, which should be modelled as [a random-access iterator](https://en.cppreference.com/w/cpp/named_req/RandomAccessIterator). Likewise, the `zip` type will _at least_ have to be modelled as [a reversible container](https://en.cppreference.com/w/cpp/named_req/ReversibleContainer).

There is a small client program in `src/5.7/zipper.cpp`. You have successfully completed this task when the program compiles and runs without error.

**Note**: you are not allowed to modify `src/5.7/zipper.cpp`.

**Implementation Hints**:
- It might be useful to think about how `std::vector`'s iterator works: it is essentially a pointer to the start of the internal buffer, and an index.
- Make sure that the required type aliases are correctly spelt and implemented.
- You will only need to implement a `const_iterator` (though `zip::iterator` should still be available). It should not be possible to modify the elements of the zipped ranges through the iterator.
- Don't overthink the `zip()` functionality: it is rather simple. What is difficult is making sure your custom iterator conforms to the Iterator interface.
- Friendship will likely be necessary.

<br />

\* [std::ranges::zip_view](https://en.cppreference.com/w/cpp/ranges/zip_view) was not in the Standard Library until C++23.
