#ifndef COMP6771_NAMESPACED_H
#define COMP6771_NAMESPACED_H

#include <string>
#include <vector>
struct celestial_body {
    std::string name;
    int pos;
};

namespace comp6771 {
    // using namespace std;
    using std::vector;

    // struct planet {
    //     std::string name;
    //     int pos;
    // };

    using planet = celestial_body;

    namespace planets {
        using terrestrial = celestial_body;

        // struct terrestrial {
        //     std::string name;
        //     int pos;
        // };
    }
}



// Hint: type aliases in modern C++ also use the "using" directive...

#endif // COMP6771_NAMESPACED_H