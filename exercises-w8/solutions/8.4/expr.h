#ifndef COMP6771_EXPR_H
#define COMP6771_EXPR_H

#include <memory>

class expr {
public:
    virtual double eval() const = 0;
    virtual ~expr() = default;
};

class plus : public expr {
public:
    plus(std::unique_ptr<expr> l, std::unique_ptr<expr> r) noexcept
    : lhs_{std::move(l)}, rhs_{std::move(r)} {}

    double eval() const override { return lhs_->eval() + rhs_->eval(); }

private:
    std::unique_ptr<expr> lhs_;
    std::unique_ptr<expr> rhs_;
};

class minus : public expr {
public:
    minus(std::unique_ptr<expr> l, std::unique_ptr<expr> r) noexcept
    : lhs_{std::move(l)}, rhs_{std::move(r)} {}

    double eval() const override { return lhs_->eval() - rhs_->eval(); }

private:
    std::unique_ptr<expr> lhs_;
    std::unique_ptr<expr> rhs_;
};

class multiply : public expr {
public:
    multiply(std::unique_ptr<expr> l, std::unique_ptr<expr> r) noexcept
    : lhs_{std::move(l)}, rhs_{std::move(r)} {}

    double eval() const override { return lhs_->eval() * rhs_->eval(); }

private:
    std::unique_ptr<expr> lhs_;
    std::unique_ptr<expr> rhs_;
};

class divide : public expr {
public:
    divide(std::unique_ptr<expr> l, std::unique_ptr<expr> r) noexcept
    : lhs_{std::move(l)}, rhs_{std::move(r)} {}

    double eval() const override { return lhs_->eval() / rhs_->eval(); }

private:
    std::unique_ptr<expr> lhs_;
    std::unique_ptr<expr> rhs_;
};

class literal : public expr {
public:
    literal(double val) noexcept : val_{val} {}

    double eval() const override { return val_; }

private:
    double val_;
};

#endif // COMP6771_EXPR_H
