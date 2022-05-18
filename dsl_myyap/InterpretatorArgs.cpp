#include "InterpretatorArgs.h"

InterpretatorArgs::InterpretatorArgs(
    std::list<std::map<std::string, Node*>*>& functions,
    std::list<std::map<std::string, Var*>*>& variablesGlobal,
    std::map<std::string, Var*>* variables,
    std::stack<Var*>& stack
) :
    functions(functions),
    variablesGlobal(variablesGlobal),
    stack(stack) {
    this->variables = variables;
}