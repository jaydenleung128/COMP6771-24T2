# Week 7 Exercises

## Q7.1.  Stack Unwinding

Write the alternative which most accurately answers the questions below.

1. What is *stack unwinding*?
- a) The process of finding an exception handler, leaving any stack frames in the same state since the OS will automatically reclaim the memory.
- b) The process of examining the stack frame to find any potential errors in our code.
- c) The process of popping stack frames until we find an exception handler for a thrown exception.
- d) The process of printing out to the terminal all the variables that exist in each stack frame as an exception propagates.
  
2. What happens during *stack unwinding*?
- a) Relevant destructors are called on objects on the way out and any exceptions thrown in a destructor (that are not caught and handled in that destructor) cause `std::terminate` to be called.
- b) Each stack frame's memory is passed to `delete` or `free()`, which will invoke the relevant destructors for objects and any exceptions thrown from a destructor cause `std::terminate` to be called.
- c) Relevant destructors are called on objects on the way out and any exceptions thrown in a destructor cause `std::terminate` to be called.
- d) Each stack frame's memory is passed to `delete` or `free()`, which will invoke the relevant destructors for objects and any exceptions thrown from a destructor (that are not caught and handled in that destructor) cause `std::terminate` to be called.

3. What issue can this potentially cause? If an issue is caused, how would we fix it?
- a) No issues are caused: every type has a destructor (even fundamental types like pointers), as required by the ISO C++ Standard.
- b) It could potentially cause an issue, depending on if we use pointers to heap memory. If we don't use pointers, there is no problem, but if we do use pointers, then we must ensure that that pointer is managed by an RAII class (such as `std::unique_pointer`).
- c) If unmanaged resources were created before an exception is thrown, they may not be appropriately released. The solution is to ensure that every resource is owned by a Standard Library container, such as `std::vector`.
- d) If unmanaged resources were created before an exception is thrown, they may not be appropriately released. The solution is to ensure that every resource is owned by an RAII-conformant class.

## Q7.2. Intelligent Pointing

Write the alternative which most accurately answers the questions below.

1. Consider the following code which currently does not use smart pointers:
```cpp
#include <thread>

void *get_memory_resource();

void very_long_lived_operation(void *data);

std::vector<std::jthread> make_threads() {
    void *data = get_unique_memory_resource();

    // Start three threads.
    // These all execute at the same time!!
    // All need access to the data
    // Don't know which one will finish first.
    return {
        std::jthread{[data](){ very_long_lived_operation(data); }},
        std::jthread{[data](){ very_long_lived_operation(data); }},
        std::jthread{[data](){ very_long_lived_operation(data); }},
    };
} // data (the pointer) went out of scope

int main() {
    // when this vector goes out of scope, the
    // program will wait for all of the threads to finish!
    auto threads = make_threads();
}
```
Which would be the appropriate smart pointer or smart pointers to replace the raw pointers with in this case and why?
- a) All pointers `std::weak_ptr`: The three threads are contending with each other, and we need to break the tie of which thread has access to the data.
- b) All pointers `std::shared_ptr`: each thread logically "owns" `data` and we cannot be sure which thread will finish first.
- c) First `std::jthread` uses a `std::unique_ptr`, the other two use `void *`: By designating one thread as the owner of the memory and the other two as observers, we ensure that `data` will never go out of scope.
- d) No change: this code is fine as it is.

2. Consider the following code which currently does not use smart pointers:
```cpp
struct node {
    struct node *parent; // go up the tree
    struct node *my_left_child; // go left of the tree
    struct node *my_right_child; // go right of the tree
};
```
Which would be the appropriate smart pointer or smart pointers to replace the raw pointers with in this case and why?
- a) All pointers `std::shared_ptr`: As a parent node, we should own the memory for the left and right child, and we need to ensure our parent outlives us.
- b) Two children pointers `std::shared_ptr`, parent pointer is `std::weak_ptr`: As a parent node, we should own the memory for the left and right child, and we need to ensure we outlive our parent. Another `std::shared_ptr` would cause a cycle, so `weak_ptr` is the better choice for it.
- c) Two children pointers `std::unique_ptr`, parent pointer is `struct node *`: As a parent node, we should own the memory for the left and right child, but need only observe our parent node. Some other node owns its memory, or it is null if we are the root node.
- d) No change: this code is fine as it is.

3. Consider the following code which currently does not use smart pointers:
```cpp
class vec {
public:
    vec(int size) : data_{new int[]{size}} {}

    ~vec() { delete[] data_; }

    const int *data() const { return data_; }
private:
    int *data_;
};
```
Which would be the appropriate smart pointer or smart pointers to replace the raw pointers with in this case and why?
- a) All pointers are `std::shared_ptr`: a future user of this class may need to take control of the underlying data and only `std::shared_ptr` will let them do that.
- b) `data_` is a `std::unique_ptr`, `data()` is `const int *`: we have exclusive ownership of `data_`, and this aligns with the semantics of `std::unique_ptr` perfectly. `data()` returns a `const int *`, so a user will not be able to modify the underlying elements and break encapsulation.
- c) All pointers are `std::unique_ptr`: A user may accidentally modify an element of the underlying data from `data()`, so to prevent this, we should deep-copy `data_` into another `std::unique_ptr`.
- d) No change: this code is fine as it is.

## Q7.3. Rethrow That Log

Often when writing exception-aware code, there are multiple places where a thrown exception needs to be logged (exceptions are, after all, _exceptional_).

C++ offers a a mechanism for both throwing and *re*throwing exceptions. Conveniently, the same keyword `throw` is used for both.

In `src/7.3/rethrower.cpp`, there is a small client program that attempts to make a connection to `db_conn` through a helper function called `make_connection`. The issue is that `db_conn::try_connection`, which `make_connection` **uses in its implementation**, doesn't throw the same exception type that `main()` in `rethrower.cpp` is expecting.

Clearly, the author of the `main()` function was expecting that `make_connection` would rethrow any exceptions caught as the description of the original exception. Specifically, if `make_connection` caught an exception in a variable `e`, it should rethrow `e.what()`.

Your task is to complete the `db_conn` and `make_connection` functions according to this behaviour such that `rethrower.cpp` compiles and produces the following output:
```text
Could not establish connection: hsmith is not allowed to login.
Could not establish connection: HeLp ;_; c0mpu73R c@ann0T c0mPut3 0w0
Could not establish connection: HeLp ;_; c0mpu73R c@ann0T c0mPut3 0w0
```
**Note**: each line is terminated with a new line.

You should implement the code in `src/7.3/rethrow.cpp`.

There is further documentation of the `db_conn` class and `make_connection` function in `src/7.3/rethrow.h`.

**Important**: you are not allowed to modify `src/7.3/rethrower.cpp`.

## Q7.4. Stuck In The Matrix

Implement the following class specification in `src/7.4/matrix.h` and/or `src/7.4/matrix.cpp`.

You will also need to write at least **five** tests in `src/7.4/matrix.test.cpp` to ensure your code is robust and correct.

### `class matrix`

A dynamic 0-indexed matrix class that supports *m* x *n* rows and columns respectively.

Internally, the matrix is stored as a flat array of `int`s. It is implementation-defined whether this matrix is stored in either [row-major or column-major order](https://en.wikipedia.org/wiki/Row-_and_column-major_order).

### Required Private Internal Representation

|Name|Type|Description|
|-----|-----|-----|
|data_|`std::unique_ptr<int[]>`|A unique pointer to an array of heap-allocated `int`s.|
|n_rows_|`std::size_t`|The number of rows of this matrix.|
|n_cols_|`std::size_t`|The number of columns of this matrix.|

### (constructors)

```cpp
/* 1 */ matrix() noexcept;
/* 2 */ matrix(std::initializer_list<std::initializer_list<int>> il);

/* 3 */ matrix(const matrix &other);
/* 4 */ matrix(matrix &&other);
```
1. **Default constructor**.
- Constructs a 0 x 0 matrix.
- No heap allocation should occur.

2. **Initialiser list constructor**.
- Constructs a matrix where the rows and columns are deduced from the nested initialiser list.
- The outer initializer list contains the rows.
- The inner initializer list contains the columns.
- The number of rows should be deduced from `std::distance(il.begin(), il.end())`.
- The number of columns should be deduced from `std::distance(il.begin()->begin(), il.begin()->end())`
  - I.e., the first element of `il` should dictate the number of columns.
- If all the columns are not the same length, throws a `std::logic_error` with message `Columns are not equal length`.
- Can assume there is at least one `int` in the initialiser list.

3. **Copy-constructor**.
- Constructs a matrix through deep-copying `other`.
- After construction, `*this == other` should be true.

4. **Move-constructor**.
- Constructs a matrix through stealing the internals of `other`.
- Afterwards, `other.dimensions() == std::make_pair(0, 0)` should be true.
  - `other.data_ == nullptr` should be true.

### Operator Overloads.
```cpp
matrix &operator=(const matrix &other);
```
**Copy-assignment operator**.
- Frees the current matrix's data
- Does a deep copy of `other`'s data.
- After the assigment, `*this == other` should be true.
- Does nothing in the case of self-assignment.

```cpp
matrix &operator=(matrix &&other) noexcept;
```
**Move-assignment operator**.
- Frees the current matrice's data.
- Steals the internals of `other`.
- Afterwards, `other.dimensions() == std::make_pair(0, 0)` should be true.
  - `other.data_ == nullptr` should be true.
- Does nothing in the case of self-assignment.

```cpp
int &operator()(std::size_t r, std::size_t c);
const int &operator()(std::size_t r, std::size_t c) const;
```
**Gets an element from the matrix**.
- If either `r` or `c` are outside the bounds of the matrix, throws a `std::domain_error` with message `(<r>, <c>) does not fit within a matrix with dimensions (<n_rows_>, <n_cols_>)`, where `<var>` is replaced with the actual value of that variable.

```cpp
bool operator==(const matrix &rhs) const noexcept;
```
**C++20 Equality operator**.
- For all `0 <= i < n_rows_` and all `0 <= j < n_cols_`, two matrices are equal if and only if:
  - `lhs(i, j) == rhs(i, j)`.
- This implies two matrices are only equal if their dimensions match and each element is equal.

### Member Functions.
```cpp
std::pair<std::size_t, std::size_t> dimensions() const noexcept;
```
Returns a {n_rows, n_cols} pair.

```cpp
const int *data() const noexcept;
```
Returns a pointer to the underlying data.

### Other Notes.
- You are not allowed to add or remove or in any way modify the spec.