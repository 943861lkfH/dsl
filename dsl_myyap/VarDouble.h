#pragma once
#include "Var.h"

class VarDouble final : public Var {
private:
    long double value;

public:
    VarDouble(const int& line, long double value);

    Var* operator + (const Var&) const;
    Var* operator - (const Var&) const;
    Var* operator * (const Var&) const;
    Var* operator / (const Var&) const;

    operator bool() const;
    operator long long() const;
    operator long double() const;
    operator std::string() const;

    Var* copy(int line) const;
};