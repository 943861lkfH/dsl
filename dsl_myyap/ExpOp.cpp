#include "ExpOp.h"

ExpOp::ExpOp(std::string name, int line) :Expression("op", name, line) {
	this->name = name;
}

std::string ExpOp::getName() {
	return name;
}

void ExpOp::action(const InterpretatorArgs& args) {
    if (args.stack.size() >= 2) {
        auto arg2 = args.stack.top();
        args.stack.pop();
        auto arg1 = args.stack.top();
        args.stack.pop();
        if (this->name == "-")
            args.stack.push(*arg1 - *arg2);
        else if (this->name == "+")
            args.stack.push(*arg1 + *arg2);
        else if (this->name == "*")
            args.stack.push(*arg1 * *arg2);
        else if (this->name == "/")
            args.stack.push(*arg1 / *arg2);
        else if (this->name == "==")
            args.stack.push(*arg1 == *arg2);
        else if (this->name == "<=")
            args.stack.push(*arg1 <= *arg2);
        else if (this->name == ">=")
            args.stack.push(*arg1 >= *arg2);
        else if (this->name == "<>")
            args.stack.push(*arg1 != *arg2);
        else if (this->name == ">")
            args.stack.push(*arg1 > *arg2);
        else if (this->name == "<")
            args.stack.push(*arg1 < *arg2);
        else if (this->name == "&&")
            args.stack.push(*arg1 && *arg2);
        else if (this->name == "||")
            args.stack.push(*arg1 || *arg2);
        delete arg1;
        delete arg2;
    }
}

std::string ExpOp::toString() const {
    return name;
}