#pragma once
#include <list>
#include <map>
#include <stack>
#include "Var.h"

class Node;

struct InterpretatorArgs {
    std::list<std::map<std::string, Node*>*>& functions;

    std::list<std::map<std::string, Var*>*>& variablesGlobal;
    std::map<std::string, Var*>* variables;

    std::stack<Var*>& stack;

    InterpretatorArgs(
        std::list<std::map<std::string, Node*>*>& functions,
        std::list<std::map<std::string, Var*>*>& variablesGlobal,
        std::map<std::string, Var*>* variables,
        std::stack<Var*>& stack
    );
};