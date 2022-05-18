#pragma once
#include <string>
#include "Expression.h"
#include "Node.h"

class ExpBody final : public Expression {
private:
    std::string name;

public:
    explicit ExpBody(std::string name, int line);

    virtual void action(const InterpretatorArgs& args) {};

    std::string toString() const;
};