# Week 1 Exercises

## Q9.1. Instantiation

Write which alternative which most accurately answers the questions below.

1. Consider the following code:
```cpp
#include <string>

template <typename T>
T my_max(T a, T b) {
    return b < a ? b : a;
}

auto main() -> int {
    auto result = 7;
    auto cat = std::string{"cat"};
    auto dog = std::string{"dog"};
    
    my_max(1, 2);
    my_max(1.0, 2.0);
    my_max(cat, dog);
    my_max('a', 'z');
    my_max(7, result);
    my_max(cat.data(), dog.data());
}
```
How many template instantiations are there (not including any from `std::string`)?
- a) 6
- b) 5
- c) 3
- d) 4

2. Consider the following code:
```cpp
template <typename T, int N>
class array {
public:
    array() : elems_{} {}

    const T *data() const;

private:
    T elems_[N];
};

template<typename T, int I>
void manipulate_array(const array<T, I> arr) {
    arr.data(); // such a complex manipulation;
}

int main() {
    void (*fp1)(const array<int, 3>) = manipulate_array;
    void (*fp2)(const array<float, 3>) = manipulate_array;
    void (*fp3)(const array<char, 4>) = manipulate_array;

    array<float, 3> arr;
    (*fp2)(arr);
}
```
How many (function, class, member) template instantiations are there?
- a) 3
- b) 4
- c) 5
- d) 6

## Q9.2. Special Selection

In `src/answers.txt`, write the alternative which most accurately answers the questions below. Each question's answer **must** be on a newline and be one of `a`, `b`, `c`, or `d` (note the lowercase).

1. Consider the following code:
```cpp
template <typename ...Ts>
struct sink {}; /* 1 */

template <typename T>
struct sink<int, T> {}; /* 2 */

template <typename T, typename ...Ts>
struct sink<int, Ts...> {}; /* 3 */

using sunk = sink<int, void>;
```
Which specialisation would be selected and why?
- a) (3): This is the only specialisation where the first template parameter matches perfectly, and `Ts...` has higher priority than a single `T`.
- b) (2): This is the only specialisation where the first template parameter matches perfectly, and `Ts...` has lower priority than a single `T`.
- c) (1): The primary template is the most general of all of the specialisations and so it is the best match.
- d) Compilation error: 2 & 3 are equally viable.

2. Consider the following code:
```cpp
template <typename T, const int *Arr>
struct sink {}; /* 1 */

template <typename T, auto Arr>
struct sink<const T, Arr> {  }; /* 2 */

template <typename T, const int *Arr>
struct sink<T&, Arr> {}; /* 3 */

constexpr int arr[3] = {};
using sunk = sink<const short&, arr>;
```
Which specialisation would be selected and why?
- a) (3): `arr` decays to a `const int *` and matches (3)'s template parameter pefectly and `T&` has higher priority over `const T` and `T`.
- b) (2): `auto` non-type template parameters are more flexible than other types and are preferred. Also, `const T` has higher preference over `T&` and `T`.
- c) (1): 2 & 3 are ambiguous since `const T` is equally viable with `T&` in this case. The compiler falls back on (1).
- d) (3): (3)'s `const int *` non-type template parameter aligns with the primary template's non-type template parameter pefectly, so it is by default the most specialised candidate.

3. Consider the following code:
```cpp
template <typename T>
void foo(T);              /* 1 */ 

template <typename T>
void foo(T *);            /* 2 */

template <>
void foo(int *);          /* 3 */ 

void foo(const int *);    /* 4 */ 

int main() {
  int p = 0;
  foo(&p);
}
```
Which specialisation would be selected and why?
- a) (1): Being the most general, this function template can be used with any argument, and so is selected as it is the best match in all cases of calls to `foo()` with a single argument.
- b) (2): In overload resolution, (1), (2), and (4) are considered. (1) does not match a pointer as well as (2) and (4), so it drops out. The compiler is able to synthesise a function that matches `int *` better than `const int *`, so (4) drops out. The compiler then instantiates (2), as (3) is an explicit specialisation, which is not allowed according to the C++ Standard.
- c) (4): `int *` is always convertible to a `const int *` and is a real function (rather than a template). Therefore, it is the best match.
- d) (3): In overload resolution, (1), (2), and (4) are considered. (1) does not match a pointer as well as (2) and (4), so it drops out. The compiler is able to synthesise a function that matches `int *` better than `const int *`, so (4) drops out. Finally, the compiler searches for any relevant specialisations of (2) and finds (3), so it is selected.

## Q9.3. Ring Temple

Implement the below `ring` class template specification in `src/9.3/ring.h`.

There is a client program in `src/9.3/ring.cpp` that uses `ring`. You have successfully completed this lab when this program compiles and produces the following output:
```
Not enough capacity
1 2 3 
42 6771 
Not enough capacity
hello world! 
yet another lazy sunday
```
**Note**: each line is terminated by a newline.

**Note**: you are not allowed to modify `src/9.3/ring.cpp`.

### `class ring`

A `ring` is a special data structure usually used for space efficient queues. It is also called a circular buffer. Essentially, a C-style array is used with a `head` and `tail` index to push and pop elements from the queue. When a user pushes an element onto the `ring`, `tail` progresses by 1. If the end of the array is reached, `tail` wraps to the start of the array. Similarly for `head`, each time the user pops an element from the `ring`, `head` is progressed by 1. When the end of the array is reached, `head` wraps around to the start.

To prevent `head` from overlapping `tail`, an extra `size` data member is kept. The added benefit of explicitly keeping track of the size is that we can prevent the user from accidentally popping from the queue when there are no more elements and from pushing onto the queue when the queue is full.

#### Template Parameters

|Name|Kind|Description|
|----|----|-----------|
|`T`|`typename`|`T` is the element type of the `ring`.|
|`N`|`std::size_t`|`N` is a `std::size_t` non-type template parameter that denotes the maximum size of the `ring`.|

#### Mandatory Private Internal Representation

|Data Member|Description|
|----|-----------|
|`std::size_t head_`|The current next index to pop from.|
|`std::size_t tail_`|The current next index to push into.|
|`std::size_t size_`|The current size of the ring.|
|`T elems_[N]`|The array of elements.|

#### (constructor)
```cpp
/* 1 */ ring(std::initializer_list<T> il);

template <typename InputIt>
/* 2 */ ring(InputIt first, InputIt last);
```
1. Initialiser list contructor.
- Pushes all of the elements of `il` into `*this`.
- Throws `std::invalid_argument{"Not enough capacity"}` if `il.size() > N`.

2. Iterator constructor.
- Pushes all of the elements denoted by the range [`first`, `last`) into `*this`.
- Throws `std::invalid_argument{"Not enough capacity"}` if `std::distance(first, last) > N`.

#### Member Functions
```cpp
auto push(const T &t) -> void;
```
Pushes a new element into the `ring`.
- Position of where to push denoted in `tail_`.
- May need to wrap `tail_` to the start of the array.
- Has no effect if the queue is full.

```cpp
auto peek() const -> const T&;
```
Return a constant reference to the head of the queue.
- Position of where the head denoted in `head_`.
- Undefined behaviour if called with an empty queue.

```cpp
auto pop() -> void;
```
Pops the head of the queue.
- Position of where to pop denoted in `head_`.
- May need to wrap `head_` to the start of the array.
- Has no effect if the queue is empty.

```cpp
auto size() const -> std::size_t;
```
Returns the size of the queue.

### Deduction Guide

It should be possible to deduce the type and size of a `ring` from the below expression:
```cpp
auto r = ring{1, 2, 3};
```
You must a Class Template Deduction Guide to allow code like this to compile.
