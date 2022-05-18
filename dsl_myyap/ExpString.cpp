#include "ExpString.h"
#include "VarString.h"

ExpString::ExpString(std::string name, int line) :   Expression("string", name, line) {
	this->name = name;
    this->line = line;
}

void ExpString::action(const InterpretatorArgs& args){
    args.stack.push(new VarString(line, name));
}

std::string ExpString::toString() const {
    return name;
}