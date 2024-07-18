#ifndef COMP6771_ORDER_H
#define COMP6771_ORDER_H

#include <iostream>

struct A { // A
    A() { std::cout << "A"; }
    ~A() { std::cout << "~A"; }
};

struct B : public virtual A { // AAB
    B() { std::cout << "B"; }
    ~B() { std::cout << "~B"; }
    A a;
};

struct C : public virtual A { // AAABC
    C() { std::cout << "C"; }
    ~C() { std::cout << "~C"; }
    B b;
};

struct D : C, B { // AAABCABAAABCAD
    D() { std::cout << "D"; }
    ~D() { std::cout << "~D"; }
    C c;
    A a;
}; 


#endif // COMP6771_ORDER_H
