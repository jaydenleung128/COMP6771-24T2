# Week 8 Exercises

## Q8.1. Visualising Tables

Write the alternative which most accurately answers the questions below.

Consider the following class hierarchy:
```cpp
struct A {
    virtual void f(int) {}
    virtual void g() {}
    void a() {}
    virtual ~A() {}
};

struct B : A {
    void f(int) override {}
    virtual void h(int) final {}
    static void b() {}
};

struct C : B {
    virtual void f(int, int) {}
    virtual void x() {}
    void h(int) override {}
};
```
Below is a representation of the incomplete vtables for `A`, `B`, and `C`:
> |A|B|C|
> |-|-|-|
> |A::f(int)|B::f(int)|**$**|
> |**!**|**@**|C::f(int, int)|
> |~A()|~B()|~C()|
> |A::g()|**#**|**%**|
> |-|B::h()|A::g()|
> |-|-|C::x()|
> |VTABLE END|VTABLE END|VTABLE END|
**Note 1**: `-` denotes an empty slot: nothing is meant to be there.

**Note 2**: This is not necesarily how a `vtable` would be created by the compiler.

1. In the slot marked **!**, what would be the most appropriate entry and why?
- a) `A::A()`: The constructor needs to be `virtual` so that derived classes and initialise their `A` subobject.
- b) `A::a()`: it is the only remaining function not in the vtable.
- c) `A::a()`: Once one method is made `virtual`, all methods should be `virtual` as a matter of good code style.
- d) Nothing: none of the above.

2. In the slot marked **@**, what would be the most appropriate entry and why?
- a) `B::b()`: this is the only method not yet listed in the `B`'s vtable.
- b) `A::~A()`: In order for `B::~B()` to function correctly, `A::~A()` also needs to be in `B`'s vtable.
- c) `B::g()`: any `virtual` method of the parent, if not explicitly overrided, has an implicit override with a default implementation that simply calls the parent's version of the method.
- d) Nothing: none of the above. 

3. In the slot marked **#**, what would be the most appropriate entry and why?
- a) `A::g()`: `B` has not explicitly overridden this method from `A`, so it inherits `A`'s `virtual` implementation.
- b) `B::g()`: any `virtual` method of the parent, if not explicitly overrided, has an implicit override with a default implementation that simply calls the parent's version of the method.
- c) `B::b()`: though it is `static`, by putting this method into `B`'s vtable, it will be able to be overridden by derived classes.
- d) Nothing: none of the above. 


4. In the slot marked **$**, what would be the most appropriate entry and why?
- a) `C::f(int)`: `C` has overriden `A::f(int)`.
- b) `C::f(int)`: `C` has overriden `B::f(int)`.
- c) `B::f(int)`: `B` explicitly overrode `A::f(int)`, but `C` has not explicitly overridden `B::f(int)`.
- d) Nothing: none of the above. 


5. In the slot marked **%**, what would be the most appropriate entry and why?
- a) `C::h(int)`: (despite the compilation error) though `B` has marked this method as `final`, the `override` specifier overrules this and successfully allows `C` to override `B::h(int)`.
- b) `C::h(int)`: This code does not compile because `C` has not explicitly added a `virtual` destructor.
- c) `B::h(int)`: (despite the compilation error) `B` has marked this method as `final`, meaning it cannot be further overridden by derived classes.
- d) Nothing: none of the above. 

## Q8.2. Static Dynamo

Write the alternative which most accurately answers the questions below.

Consider the 
```cpp
#include <iostream>

struct banana {
    virtual void f() {
		std::cout << "banana ";
	}
};

struct door : banana {
	void f() override {
		std::cout << "door ";
	}
};

int main() {
	banana b;
	door d;
	b = d;
	banana &bref = dynamic_cast<banana&>(b);
	door &dref = d;
	banana &dbref = dynamic_cast<banana&>(d);
	b.f();
	d.f();
	bref.f();
	dref.f();
	dbref.f();
}
```

1. For each of `bref`, `dref`, and `dbref`: by the end of the program, what is this variable's static and dynamic type?
- a)
    - `bref`: static: `door&`, dynamic: `banana&`
    - `dref`: static: `banana&`, dynamic: `door&`
    - `dbref`: static: `door&`, dynamic: `door&`
- b)
    - `bref`: static: `door&`, dynamic: `banana&`
    - `dref`: static: `door&`, dynamic: `door&`
    - `dbref`: static: `door&`, dynamic: `banana&`
- c)
    - `bref`: static: `banana&`, dynamic: `door&`
    - `dref`: static: `door&`, dynamic: `door&`
    - `dbref`: static: `banana&`, dynamic: `door&`
- d)
    - `bref`: static: `banana&`, dynamic: `banana&`
    - `dref`: static: `door&`, dynamic: `door&`
    - `dbref`: static: `banana&`, dynamic: `door&`

2. Is there anything wrong with the assignment `b = d`?
- a) Yes: we have not defined `operator=` for `banana`.
- b) Yes: since `b` is a `banana`, assigning `d` to it will cause `d`'s `door` half to be sliced off. This is the object slicing problem.
- c) No: this code is perfectly legal code.
- d) Maybe: since `sizeof(banana) == sizeof(door)`, the result of this expression depends on the version of the compiler.

3. In general, how is the object-slicing problem avoided?
- a) It cannot be avoided: C++'s value semantics preclude this possibility.
- b) Only use `std::unique_ptr` in code that uses polymorphic objects.
- c) When dealing with polymorphic objects, always make sure when the static and dynamic types don't align to use either a pointer or a reference.
- d) Make sure the size of polymorphic classes is always the same so that even if slicing occurs, there are no side-effects.

## Q8.3. Order Of The Inheritance

Recall the order of construction and destruction in the face of base classes in C++:
* Construction:
    1. `virtual` base classes (assuming all parents also inherit that class virtually) in declaration order.
    2. Non-`virtual` bases in declaration order.
    3. Data members in declaration order.
    4. `this`'s constructor.

* Destructor:
    1. `this`'s destructor.
    2. Destructors of data members in reverse-declaration order.
    3. Non-`virtual` bases in reverse-declaration order.
    4. `virtual` base classes in reverse-declaration order.

In order to test their knowledge out, a budding C++ expert in `src/8.3/ordered.cpp` created a small program with this output:
```text
AAABCABAAABCADAAAB
~B~A~A~A~D~A~C~B~A~A~A~B~A~C~B~A~A~A
```
**Note**: each line is terminated by a newline.

This output consists of some configuration of inheritance and composition of four `struct`s that have been stubbed in `src/8.3/order.h` and `src/8.3/order.cpp`.

Your task is figure out the configuration of inheritance and composition of these four `struct`s such that `ordered.cpp` compiles and produces the above output. You have successfully completed this lab when your program does so.

**Important**: You are not allowed to modify `src/8.3/ordered.cpp`.

## Q8.4. Calculated Expression

A common pattern in compilers is to represent the various elements of a programming language as classes and to naturally model the Abstract Synax Tree* as a class hierarchy.

Inspired by compiler writers of old, a budding C++ expert wrote a small program in `src/8.4/expression.cpp` which, using such a class hierarchy that represents fundamental arithmetic (`+`, `-`, `*`, and `/`), calculates a very special number and outputs it (with some supplementary text) to the terminal.

Unfortunately, this programmer was not elite enough to finished the class hierarchy implementation. He was, however, able to stub out the Abstract Base Class which the required base classes should derive from.

Your task is to complete what this young and enthusiastic programmer set out to do such that `expression.cpp` successfully compiles, runs, and produces the following output:
```text
COMP6771: Advanced C++ Programming
```
**Note**: each line is terminated with a newline.

You should implement the rest of the solution in `src/8.4/expr.h` and/or `src/8.4/expr.cpp`.

*: not required knowledge.