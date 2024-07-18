#ifndef COMP6771_VEC3_H
#define COMP6771_VEC3_H

struct vec3 {
    vec3() : vec3(0, 0, 0) {}
    explicit vec3(double c) : vec3(c, c, c) {}
    vec3(double a, double b, double c) : x{a}, y{b}, z{c} {}

    union {
        double x;
        double r;
        double s;
    };
    union {
        double y;
        double g;
        double t;
    };
    union {
        double z;
        double b;
        double p;
    };
};

#endif // COMP6771_VEC3_H
