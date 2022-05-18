#include "ExpInt.h"
#include "VarInt.h"

ExpInt::ExpInt(std::string name, int line) :Expression("int", name, line) {
	this->name = name;
    this->line = line;
}

void ExpInt::action(const InterpretatorArgs& args){
    int value = stoi(name);
    args.stack.push(new VarInt(line, value));
}

std::string ExpInt::toString() const {
    return name;
}