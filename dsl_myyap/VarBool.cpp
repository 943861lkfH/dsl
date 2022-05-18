#include "VarBool.h"
#include "VarInt.h"
#include "VarDouble.h"
#include "VarString.h"


VarBool::VarBool(const int& line, bool value) :
    Var(line, BOOL_VAR),
    value(value) {}

Var* VarBool::operator + (const Var& second) const {
    switch (second.getType()) {
    case BOOL_VAR:
        return new VarBool(line, (bool)*this || (bool)second);
    case INTEGER_VAR:
        return new VarInt(line, (long long)*this + (long long)second);
    case DOUBLE_VAR:
        return new VarDouble(line, (long double)*this + (long double)second);
    case STRING_VAR:
        return new VarString(line, (std::string) * this + (std::string) second);
    /*case LIST_VAR: {
        auto list = (std::list<Var*>) * this;
        list.splice(list.end(), (std::list<Var*>) second);
        return new VarList(line, list);
    }*/

    }
        return NULL;
}

Var* VarBool::operator - (const Var& second) const {
    switch (second.getType()) {
    case BOOL_VAR:
    case INTEGER_VAR:
        return new VarInt(line, (long long)*this - (long long)second);
    case DOUBLE_VAR:
        return new VarDouble(line, (long double)*this - (long double)second);
    case STRING_VAR:
    case LIST_VAR:
        return second.operator - (*this);
    }
    return NULL;
}

Var* VarBool::operator * (const Var& second) const {
    switch (second.getType()) {
    case BOOL_VAR:
    case INTEGER_VAR:
        return new VarInt(line, (long long)*this * (long long)second);
    case DOUBLE_VAR:
        return new VarDouble(line, (long double)*this * (long double)second);
    case STRING_VAR:
    case LIST_VAR:
        return second.operator * (*this);
    }
    return NULL;
}

Var* VarBool::operator / (const Var& second) const {
    const auto& type = second.getType();
    if (type == STRING_VAR || type == LIST_VAR) {
        return second.operator / (*this);
    }
    else {
        return new VarDouble(line, (long double)*this / (long double)second);
    }
}

VarBool::operator bool() const {
    return value;
}

VarBool::operator long long() const {
    return (long long)value;
}

VarBool::operator long double() const {
    return (long double)value;
}

VarBool::operator std::string() const {
    return (value ? "true" : "false");
}

Var* VarBool::copy(int line) const {
    return new VarBool(line, value);
}