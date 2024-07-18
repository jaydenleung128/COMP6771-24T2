# Week 4 Exercises

## Q4.1. Namespaces & Scopes

Consider the following program:

```cpp
#include <iostream>

namespace {
    auto i = 42;
}

namespace comp6771 {
    auto i = 6771;

    auto foo(int) -> void {
        std::cout << "comp6771::foo(int)" << std::endl;
    }
}

namespace comp6772 {
    auto foo(int) -> void {
        std::cout << "comp6772::foo(int)" << std::endl;
    }

    auto foo(char) -> void {
        std::cout << "comp6772::foo(char)" << std::endl;
    }
}

namespace comp6773 {
    struct uchar {
        unsigned char c;
    };

    auto bar(uchar) -> void {
        std::cout << "comp6773::bar(comp6773::uchar)" << std::endl;
    }
}

int main() {
    std::cout << i << std::endl;        
    {
        int i = 0;                      
        std::cout << i << std::endl;    

        using ::i;                      
        std::cout << i << std::endl;    
    }

    comp6771::foo(i);                   
    comp6772::foo(i);                   

    using namespace comp6771;           
    using namespace comp6772;           

    foo(i);                                                                     

    foo('c');                         

    auto uc = comp6773::uchar{'c'};     
    bar(uc);                            
}
```

Some of the lines of this program are ill-formed according to C++'s rules about namespaces and scopes.

Figure out which lines of this program are ill-formed - write them dowon!

**Hint**: you should pretend you are like a compiler and can only look at this source file as it is. Don't try and remove any lines as that could make subsequent lines become well-formed.


## Q4.2. Constructing Destruction

Write the alternative which most accurately answers the questions below.

Consider the following structure:
```cpp
struct object {
    object() {
        std::cout << "ctor ";
    }

    object(const object &) {
        std::cout << "copy-ctor ";
    }

    ~object() {
        std::cout << "dtor ";
    }
};
```

1. What is the output of the below code and why?
```cpp
{
    std::cout << "Pointer: ";
    std::list<object *> l;
    object x;
    l.push_back(&x);
}
```
- a) `Pointer: ctor ctor dtor dtor`. `l` is a list of `object`-derived types and `x` is an `object`, so the constructor and destructor for `object` will run for both.
- b) `Pointer: ctor dtor`. Variables are destructed in the reverse-order of definition on the stack, so to prevent a double-free bug, `l`'s single element (the address of `x`) only has the constructor and destructor run for it.
- c) `Pointer: ctor dtor`. The only `object` whose lifetime ends in this code block is `x`, and the list `l` is irrelevant.
- d) `Pointer: ctor ctor dtor dtor`. `l`'s default constructor creates an `object *` instance and a second instance is created when the address of `x` is pushed back. Two constructions implies two destructions.

2. What is the output of the below code and why?
```cpp
{
    std::cout << "\nValue: ";
    std::list<object> l;
    object x;
    l.push_back(x);
}
```
- a) `Value: ctor copy-ctor dtor dtor`. The default constructor of `object` is called when `x` comes into scope and the copy constructor is called when `x` is pushed back into `l`. At the end of scope, `x` is destructed first and, since `l` holds `object`s by value, its single element is destructed second.
- b) `Value: ctor copy-ctor dtor dtor`. `x` is default-constructed and destructed as per usual, but the temporary that is created by passing `x` into `push_back()` is copy-constructed and destructed in that expression.
- c) `Value: ctor copy-ctor copy-ctor dtor dtor dtor`. `x` is default-constructed and destructed as per usual, but the temporary that is created in the call to `l.push_back()` _and_ the resulting element of `l` are copy-constructed and destructed.
- d) `Value: ctor copy-ctor dtor copy-ctor dtor dtor`. `x` is default-constructed and destructed as per usual, but the temporary that is created in the call to `push_back()` has its lifetime end at the end of that expression before it is copied into `l`. At the end of scope, `l`'s single element is also destructed.


## Q4.3. Defaults & Deletes

Write the alternative which most accurately answers the questions below.

1. Consider the below code:
```cpp
struct point2i {
    int x;
    int y;
};
```
Is this class-type default-constructible and why?
- a) No: We need to opt-in to a default aggregate initialiser.
- b) Yes: default aggreggate-initialisation would leave `x` and `y` uninitialised.
- c) No: This is a C-style struct; it has no default constructor.
- d) Yes: default aggregate-initialisation would set `x` and `y` to `0`.

2. Consider the below code:
```cpp
class employee {
public:
    employee(int employeeno);

private:
    int employeeno;
};
```
Is this class-type default-constructible and why?
- a) Yes: the compiler can automatically synthesise the default constructor if we don't provide one.
- b) No: a user-provided constructor prevents automatic synthesis of a default constructor.
- c) No: we have not provided an in-class member initialiser.
- d) Yes: `int` itself has a default constructor, so `employee`'s default constructor simply delegates to `int`'s one.

3. Consider the below code:
```cpp
struct point2i {
    point2i() = default;
    point2i(int x = 42, int y = 6771);

    int x;
    int y;
};
```
Is this class-type default-constructible and why?
- a) No: the two provided constructors are ambiguous when called with 0 arguments, so this code won't compile.
- b) Yes: we have explicitly defaulted the default constructor.
- c) Yes: Though both constructors can be called with 0 arguments, the compiler prefers the explicitly defaulted default-constructor.
- d) Yes: Though both constructors can be called with 0 arguments, in overload resolution the second constructor has higher priority, so it will be called.

4. Consider the below code:
```cpp
struct point2i {
    point2i() = default;
    point2i(const point2i &) = delete;
    point2i(point2i &&) = delete;
};

point2i get_point() { return point2i{}; }

point2i p = get_point();
```
Will this code compile and why?
- a) Yes: the default constructor will be called for `p`'s initialisation
- b) No: `point2i(point2i &&)` is invalid syntax.
- c) No: `point2i` is not copyable at all, so `p` cannot be initialised.
- d) Yes: `point2i` has no data members, so even though the copy and move constructors are deleted, the compiler knows that those constructors would have had no effect anyway.

5. Consider the below code:
```cpp
struct guard {
    guard() = default;
    guard(const guard &) = delete;
    guard(guard &&) = delete;
};

struct outer {
    guard g;
};
```
Is the `outer` class-type default-constructible or copyable and why?
- a) Neither default-constructible nor copyable: we have not explicitly told the compiler that we want `outer` to have the default constructor and copy/move constructors generated for us.
- b) Default-constructible but not copyable: `guard`'s explicitly deleted copy/move constructor prevents the implicitly generated copy/move constructors for `outer`. For a similar reason, `guard` does allow for the implicitly generated default constructor.
- c) Won't compile: `guard` prevents the implicit copy/move constructors for `outer` to be generated, as well the default constructor. Therefore, this class cannot be constructed, which is a compiler error.
- d) Default-constructible and copyable: `guard` has no effect on the implicitly generated default, copy, and move constructors for `outer` since it is a `struct`. If `outer` were a `class`, it would only be default-constructible, however.


## Q4.4. Construction Confusion

Write the alternative which most accurately answers the questions below. 

1. Consider the below code snippet:
```cpp
std::vector<int> a(1, 2);
```
What is this line doing?
- a) Default construction.
- b) Construction via Direct Initialisation.
- c) Function declaration.
- d) From C++11 onwards, this is invalid syntax; won't compile.

2. Consider the below code snippet:
```cpp
std::vector<int> a{1, 2};
```
What is this line doing?
- a) From C++11 onwards, this is invalid syntax; won't compile.
- b) Function declaration.
- c) Construction via Aggregate Initialisation.
- d) Construction via Uniform Initialisation.

3. Consider the below code snippet:
```cpp
std::vector<int> b = {1, 2};
```
What is this line doing?
- a) Construction via Copy Initialisation.
- b) Construction by Assignment Initialisation.
- c) Construction via Uniform Initialisation.
- d) Construction via Direct Initialisation.

4. Consider the below code snippet:
```cpp
std::vector<int> a{1, 2};
std::vector<int> c = a;
```
What is this line doing?
- a) Construction via Copy Initialisation
- b) Copy assignment of `a` to `c`.
- c) Construction via Assignment Initialisation
- d) `c` is "stealing" the data members of `a` to construct itself.

5. Consider the below code:
```cpp
std::vector<int> a{1, 2};
std::vector<int> c;
c = a;
```
What is this line doing?
- a) Reconstruction of `c` from `a`.
- b) Construction via Copy Initialisation.
- c) Copy assignment of `a` to `c`.
- d) Aggregate assignment of `a` to `c`.


## Q4.5. Namespacing Out

In `src/4.5/namespaced.cpp`, we have provided the below `main()` function:
```cpp
int main() {
    namespace spaceland = comp6771;

    // should be an alias for std::vector.
    auto v = spaceland::vector{6771};
    
    // name: earth, position from sun: 3
    // a planet is a kind of 
    auto earth = spaceland::planet{"earth", 3};

    // should produce an object with the same type as the "earth" variable above.
    auto old_earth = spaceland::planets::terrestrial{"earth", 3};

    std::cout << v[0] << std::endl;
    std::cout << earth.name << std::endl;
    std::cout << old_earth.pos << std::endl;
}
```

In `src/4.4/namespaced.h`, implement the rest of the missing namespace functionality such that this code compiles and produces this output (note the newline at the end):
```txt
6771
earth
3
```
There is a plain-old-data struct in `src/4.5/namespaced.h` that may be used as a `planet` type.

**Note**: you are not allowed to modify `src/4.5/namespaced.cpp`.

**Hint**: it does not matter how you implement the namespaces in the header file -- if your code compiles and produces the above output, then it is correct.


## Q4.6. Ferrari++

Implement the following class specification in `src/4.6/ferrari.h` and/or `src/4.6/ferrari.cpp`.

| Method | Description |
|------|------|
|`ferrari(const std::string &owner, int modelno)`| This constructor should initialise the object state to keep track of the owner name and model number. Speed is initially 0. |
|`ferrari()`| This constructor should default-initialise the object's state so that its owner name is "unknown" and its model number is `6771`. Speed is initially 0.|
|`std::pair<std::string, int> get_details()`.| Returns this Ferrari's owner and model number.|
|`void drive(int spd)`.| Start driving at speed `spd`. If no speed is given, it should default to `88`.|
|`std::string vroom()`.| Returns a string depending on how fast this Ferrari is currently moving. If the speed is strictly less than 20, it should return the empty string. If `20 <= speed < 80`, it should return "vroom!!". Otherwise, it should return "VROOOOOOOOM!!!".|

**Note**: You need to ensure your code is const-correct. Which methods should be const-qualified has intentionally been left out.

When implementing this class, you should ensure you are using modern C++ best practices, such as member initialiser lists, delegating constructors, etc. You should check with your tutor to make sure that your style aligns with modern practices.

In `src/4.6/ferrari.test.cpp`, you will also need to write at least **five** tests to make sure your code is correct.


## Q4.7. Value-centric C++ (1/2)

C++ has value semantics by default (rather than reference semantics like other languages, such as Java). Classes allow developers to write their own value-types that act, look, and feel like the regular built-in types like `int` or `double`.

In this exercise we begin to create our own value-type representing a rational number. Rational numbers are any number that can be represented as a fraction with integer numerator and denominator. Note that `x/0` for any `x` is not a rational number.

In `src/4.7/rational.cpp` and associated files, implement the `rational_number` class and write at least **three** tests for it.

The class should have:
- a static public data member `null`, which represents "no" rational number. This should be implemented as an empty `std::optional<rational_number>`.
- a public static member function `auto make_rational(int num, int denom) -> std::optional<rational_number>` that returns either a rational number or the above static data member if `denom == 0`.
- a private constructor, so that a user cannot accidentally create an invalid rational number (all creation must use `make_rational`).
- the four arithmetic operations `add(), sub(), mul(), div()` as friend functions so that, for `r1` and `r2` which have type `rational_number`, one may write: `add(r1, r2)`, etc.. The return type for `add(), sub(), mul()` should be `rational_number`, but for `div()` it should be `std::optional<rational_number>`.
- the two equality operations `eq` and `ne` so that, for `r1` and `r2` which have type `rational_number`, one may write `if (eq(r1, r2)) { ... }`. The return type for both of these functions should be `bool`.
    - **Hint**: equality for fractions doesn't necesarily mean the numerators and denominators are equal! E.g., 1/2 == 2/4...
- a public method `auto value() -> double` which returns the quotient of the numerator and the denominator as a `double`.

The size of every instance of your class should be no bigger than `16 bytes`.


## Q4.8. GLSL++

The Open**GL** **S**hader **L**anguage (GLSL) is a C/C++-like language used to write shader programs that can run on GPUs.

One convenient feature of the GLSL built-in type `vec3` is that you can access its components by various names. For example:
- `v.x`: access the 1st component in `v` as a spatial dimension.
- `v.r`: access the 1st component in `v` as a colour dimension.
- `v.s`: access the 1st component in `v` as a texture dimension.

In all, there are three sets of syntactic sugar:
- `x`, `y`, `z`: for 1st, 2nd, and 3rd componenets of a `vec3`.
- `r`, `g`, `b`: for 1st, 2nd, and 3rd componenets of a `vec3`.
- `s`, `t`, `p`: for 1st, 2nd, and 3rd componenets of a `vec3`.

In `src/4.8/vec3.h` and/or `src/4.8/vec3.cpp`, complete the below specification.
When you are done, write at least **three** tests in `src/4.8/vec3.test.cpp`.

### Public Data Members

| Data Member | Type |
|--------|---------|
| `v.x`<br/>`v.r`<br/>`v.s` | `double`|
| `v.y`<br/>`v.g`<br/>`v.t` | `double`|
| `v.z`<br/>`v.b`<br/>`v.p` | `double`|

`x`, `r`, and `s` should refer to the same data member.
Likewise, `y`, `g`, and `t` should refer to the same data member.
Similarly, `z`, `b`, and `p` should refer to the same data member.

Therefore, `sizeof(vec3) == 3 * sizeof(double)` should be true.

**Hint**: you may find [this page on unions](https://en.cppreference.com/w/cpp/language/union) useful. Particularly, anonymous unions inside of class-types.

### Constructors

```cpp
/* 1 */ vec3();
/* 2 */ vec3(double c);
/* 3 */ vec3(double a, double b, double c);
```
1) Default constructor.
- Initialise this vector to contain 0 in each component.

2) Broadcast Component Constructor.
- Initialise this vector, setting all components to `c`.

**Note**: you must ensure the below code snippet cannot happen:
```cpp
// should fail to compile.
vec3 foo() { return 1.0; }
vec3 v = foo();
```

3) All Component Constructor.
- Initialise this vector so the first component is `a`, the second is `b`, and the third is `c`.

### Copy-control

Your class should be copyable and destructible.

### Member Functions.

None.

Aside from the constructors, `vec3` is intended to be a plain data struct, so it is OK to access its data members directly.


