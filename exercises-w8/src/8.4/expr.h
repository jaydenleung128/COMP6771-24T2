#ifndef COMP6771_EXPR_H
#define COMP6771_EXPR_H

#include <memory>

class expr {
public:
    virtual double eval() const = 0;
    virtual ~expr() = default;
};

#endif // COMP6771_EXPR_H
