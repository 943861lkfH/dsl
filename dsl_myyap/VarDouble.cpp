#include "VarDouble.h"
#include "VarString.h"
//#include "VarList.h"


VarDouble::VarDouble(const int& line, long double value) :
    Var(line, DOUBLE_VAR),
    value(value) {}

Var* VarDouble::operator + (const Var& second) const {
    const auto& type = second.getType();
    if (type == STRING_VAR) {
        return new VarString(line, (std::string)*this + (std::string) second);
    }
    /*else if (type == LIST_VAR) {
        auto list = (std::list<Var*>) * this;
        list.splice(list.end(), (std::list<Var*>) second);
        return new VarList(line, list);
    }*/
    else {
        return new VarDouble(line, (long double)*this + (long double)second);
    }
}

Var* VarDouble::operator - (const Var& second) const {
    const auto& type = second.getType();
    if (type == STRING_VAR || type == LIST_VAR) {
        return second.operator - (*this);
    }
    else {
        return new VarDouble(line, (long double)*this - (long double)second);
    }
}

Var* VarDouble::operator * (const Var& second) const {
    const auto& type = second.getType();
    if (type == STRING_VAR || type == LIST_VAR) {
        return second.operator * (*this);
    }
    else {
        return new VarDouble(line, (long double)*this * (long double)second);
    }
}

Var* VarDouble::operator / (const Var& second) const {
    const auto& type = second.getType();
    if (type == STRING_VAR || type == LIST_VAR) {
        return second.operator / (*this);
    }
    else {
        return new VarDouble(line, (long double)*this / (long double)second);
    }
}

VarDouble::operator bool() const {
    return (bool)value;
}

VarDouble::operator long long() const {
    return (long long)value;
}

VarDouble::operator long double() const {
    return value;
}

VarDouble::operator std::string() const {
    return std::to_string(value);
}

Var* VarDouble::copy(int line) const {
    return new VarDouble(line, value);
}