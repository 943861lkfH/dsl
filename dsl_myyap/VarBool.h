#pragma once
#include "Var.h"

class VarBool final : public Var {
private:
    const bool value;

public:
    explicit VarBool(const int& line, bool value);

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