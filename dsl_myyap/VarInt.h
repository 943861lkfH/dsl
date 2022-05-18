#pragma once
#include "Var.h"

class VarInt final : public Var {
private:
    long long value;

public:
    explicit VarInt(int line, long long value);

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