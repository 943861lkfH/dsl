#include "Var.h"
#include "VarBool.h"
#include "ExpVar.h"


Var::Var(const int& line, const VarType& type) :
    line(line),
    type(type) {}

Var::~Var() = default;

std::string Var::getTypeName() const {
    switch (type) {
    case BOOL_VAR:
        return "'bool'";
    case INTEGER_VAR:
        return "'int'";
    case DOUBLE_VAR:
        return "'double'";
    case STRING_VAR:
        return "'string'";
    case LIST_VAR:
        return "'list'";
    case MAP_VAR:
        return "'map'";
    }
    return NULL;
}

//void Var::throwExcOperator(const std::string & op) const {
//    throw ExcVar("wrong operand '" + op + "' for type " + getTypeName(), line);
//}
//
//void Var::throwExcConvert(const std::string & value, const std::string & typeName) const {
//    throw ExcVar("unable to convert '" + value + "' to type " + typeName, line);
//}

Var* Var::operator + (const Var&) const {

    return NULL;
}

Var* Var::operator - (const Var&) const {
    return NULL;
}

Var* Var::operator * (const Var&) const {
    return NULL;
}

Var* Var::operator / (const Var&) const {
    return NULL;
}

Var* Var::operator < (const Var & second) const {
    if (second.getType() == STRING_VAR) {
        return new VarBool(line, (std::string)*this < (std::string) second);
    }
    else {
        return new VarBool(line, (long double)*this < (long double)second);
    }
}

Var* Var::operator <= (const Var & second) const {
    if (second.getType() == STRING_VAR) {
        return new VarBool(line, (std::string) * this <= (std::string) second);
    }
    else {
        return new VarBool(line, (long double)*this <= (long double)second);
    }
}

Var* Var::operator > (const Var & second) const {
    if (second.getType() == STRING_VAR) {
        return new VarBool(line, (std::string)*this > (std::string)second);
    }
    else {
        return new VarBool(line, (long double)*this > (long double)second);
    }
}

Var* Var::operator >= (const Var & second) const {
    if (second.getType() == STRING_VAR) {
        return new VarBool(line, (std::string) * this >= (std::string) second);
    }
    else {
        return new VarBool(line, (long double)*this >= (long double)second);
    }
}

Var* Var::operator == (const Var & second) const {
    return new VarBool(line, ((bool)*this != (bool)second));
}

Var* Var::operator != (const Var & second) const {
    return new VarBool(line, ((bool)*this == (bool)second));
}

Var* Var::operator && (const Var & second) const {
    return new VarBool(line, ((bool)*this && (bool)second));
}

Var* Var::operator || (const Var & second) const {
    return new VarBool(line, ((bool)*this || (bool)second));
}

Var::VarType Var::getType() const {
    return type;
}

Var::operator bool() const {
    return NULL;
}

Var::operator long long() const {
    return NULL;
}

Var::operator long double() const {
    return NULL;
}
//
//Var::operator std::list<Var*>() const {
//    return { copy(line) };
//}
//
//Var::operator std::map<Var*, Var*>() const {
//    throwExcConvert(std::string(*this), "'map'");
//}