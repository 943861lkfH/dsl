#include "VarString.h"


VarString::VarString(int line, std::string value) :
    Var(line, STRING_VAR),
    value(value) {}

Var* VarString::operator + (const Var& second) const {
    /*if (second.getType() == LIST_VAR) {
        auto list = (std::list<Var*>) * this;
        list.splice(list.end(), (std::list<Var*>) second);
        return new VarList(line, list);
    }
    else {*/
        return new VarString(line, (std::string) * this + (std::string) second);
    
}

Var* VarString::operator - (const Var& second) const {
    return super::operator - (second);
}

Var* VarString::operator * (const Var& second) const {
    if (second.getType() == INTEGER_VAR) {
        auto str = (std::string) * this;
        std::string result;
        for (int i = 0; i < (long long)second; i++) {
            result += str;
        }
        return new VarString(line, result);
    }
    else {
        return super::operator * (second);
    }
}

Var* VarString::operator / (const Var& second) const {
    return super::operator/(second);
}

VarString::operator bool() const {
    return !value.empty();
}

VarString::operator long long() const {

    return NULL;
}

VarString::operator long double() const {

    return NULL;
}

VarString::operator std::string() const {
    return value;
}

Var* VarString::copy(int line) const {
    return new VarString(line, value);
}