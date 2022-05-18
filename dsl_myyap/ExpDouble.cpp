#include "ExpDouble.h"
#include "VarDouble.h"

ExpDouble::ExpDouble(std::string name, int line) :Expression("double", name, line) {
	this->name = name;
    this->line = line;
}

void ExpDouble::action(const InterpretatorArgs& args){
    double value = atof(name.c_str());
    args.stack.push(new VarDouble(line, value));
}

std::string ExpDouble::toString() const{
    return name;
}