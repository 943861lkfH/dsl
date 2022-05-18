#include "ExpVar.h"

ExpVar::ExpVar(std::string name, int line) :Expression("var", name, line) {
	this->name = name;
    this->line = line;
}

void ExpVar::action(const InterpretatorArgs& args) {
    for (auto scope : args.variablesGlobal) {
        if (callVariableFrom(scope, args.stack)) {
            return;
        }
    }
}

std::string ExpVar::toString() const {
    return name;
}

bool ExpVar::callVariableFrom(std::map<std::string, Var*>* container, std::stack<Var*>& stack) {
    auto it = container->find(name);
    if (it != container->end()) {
        stack.push(it->second->copy(line));
        return true;
    }
    return false;
}