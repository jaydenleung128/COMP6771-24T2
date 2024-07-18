#include <iostream>
#include <list>

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

int main(void) {
    
    // {
    //     std::cout << "Pointer: ";
    //     std::list<object *> l;
    //     object x; //ctor
    //     l.push_back(&x);
    //     // dtor
    // }


    {
        std::cout << "\\nValue: ";
        std::list<object> l;
        object x; //ctor
        l.push_back(x); //copy-ctor
        // dtor dtor
    }

    return 0;
}