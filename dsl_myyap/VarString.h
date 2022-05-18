#pragma once
#include "Var.h"

class VarString final : public Var {
private:
    const std::string value;

public:
    explicit VarString(int line, std::string value);

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