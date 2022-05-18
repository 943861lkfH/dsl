#include "ExpBool.h"
#include "VarBool.h"

ExpBool::ExpBool(std::string name, int line) :Expression("bool", line) {
    if (name == "true")
        this->name = true;
    else this->name = false;
    this->line = line;
}

void ExpBool::action(const InterpretatorArgs& args){
    args.stack.push(new VarBool(line, name));
}

std::string ExpBool::toString() const {
    return (name ? "true" : "false");
}