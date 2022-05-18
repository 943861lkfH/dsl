#include "VarInt.h"
#include "VarDouble.h"
#include "VarString.h"


VarInt::VarInt(int line, long long value) :
    Var(line, INTEGER_VAR),
    value(value) {}

Var* VarInt::operator + (const Var& second) const {
    switch (second.getType()) {
    case BOOL_VAR:
    case INTEGER_VAR:
        return new VarInt(line, (long long)*this + (long long)second);
    case DOUBLE_VAR:
        return new VarDouble(line, (long double)*this + (long double)second);
    /*case LIST_VAR: {
        auto list = (std::list<Var*>) * this;
        list.splice(list.end(), (std::list<Var*>) second);
        return new VarList(line, list);
    }*/
    case STRING_VAR:
        return new VarString(line, (std::string) * this + (std::string) second);
    }
    return NULL;
}

Var* VarInt::operator - (const Var& second) const {
    const auto& type = second.getType();

    if (type == BOOL_VAR || type == INTEGER_VAR) {
        return new VarInt(line, (long long)*this - (long long)second);
    }
    else if (type == DOUBLE_VAR) {
        return new VarDouble(line, (long double)*this - (long double)second);
    }
    else {
        return second.operator - (*this);
    }
}

Var* VarInt::operator * (const Var& second) const {
    switch (second.getType()) {
    case BOOL_VAR:
    case INTEGER_VAR:
        return new VarInt(line, (long long)*this * (long long)second);
    case DOUBLE_VAR:
        return new VarDouble(line, (long double)*this * (long double)second);
    case LIST_VAR:
        return second.operator * (*this);
    case STRING_VAR: {
        auto str = (std::string) second;
        std::string result;
        for (int i = 0; i < (long long)*this; i++) {
            result += str;
        }
        return new VarString(line, result);
    }
    }
                   return NULL;
}

Var* VarInt::operator / (const Var& second) const {
    const auto& type = second.getType();
    if (type == STRING_VAR || type == LIST_VAR) {
        return second.operator / (*this);
    }
    else {
        return new VarDouble(line, (long double)*this / (long double)second);
    }
}

VarInt::operator bool() const {
    return (bool)value;
}

VarInt::operator long long() const {
    return value;
}

VarInt::operator long double() const {
    return (long double)value;
}

VarInt::operator std::string() const {
    return std::to_string(value);
}

Var* VarInt::copy(int line) const {
    return new VarInt(line, value);
}