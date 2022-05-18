#pragma once
#include <string>
#include <list>
#include <map>

class Var {
public:
    enum VarType {
        BOOL_VAR,
        INTEGER_VAR,
        DOUBLE_VAR,
        STRING_VAR,
        LIST_VAR,
        MAP_VAR,
    };

    Var(const int& line, const VarType& type);
    virtual ~Var();

    virtual Var* operator + (const Var&) const;
    virtual Var* operator - (const Var&) const;
    virtual Var* operator * (const Var&) const;
    virtual Var* operator / (const Var&) const;


    Var* operator <  (const Var&) const;
    Var* operator <= (const Var&) const;
    Var* operator >  (const Var&) const;
    Var* operator >= (const Var&) const;
    Var* operator == (const Var&) const;
    Var* operator != (const Var&) const;
    Var* operator && (const Var&) const;
    Var* operator || (const Var&) const;

    virtual operator bool() const = 0;
    virtual operator long long() const = 0;
    virtual operator long double() const = 0;
    virtual operator std::string() const = 0;
    /*virtual operator std::list<Var*>() const;
    virtual operator std::map<Var*, Var*>() const;*/

    VarType getType() const;

    virtual Var* copy(int line) const = 0;

private:
    const VarType type;

    std::string getTypeName() const;

    /*void throwExcOperator(const std::string& op)                                 const;
    void throwExcConvert(const std::string& value, const std::string& typeName) const;*/

protected:
    typedef Var super;
    const int line;
};