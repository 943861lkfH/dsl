#include "Interpretator.h"

Interpretator::Interpretator(std::map<std::string, Node*>* functions) {
    this->functions.push_front(functions);
    variables = new std::map<std::string, Var*>();
}

Interpretator::Interpretator(
    const std::list<std::map<std::string, Node*>*>& functions,
    const std::list<std::map<std::string, Var*>*>& variablesGlobal
) :
    functions(functions),
    variablesGlobal(variablesGlobal) {
    variables = new std::map<std::string, Var*>();
}

Interpretator::~Interpretator() {
    for (const auto& var : *variables) {
        delete var.second;
    }
    delete variables;
    cleanStack();
}

void Interpretator::execute(Node* tree) {
    for (auto node : tree->getChildren()) {
        executeChild(node);
        cleanStack();
    }

    tree->getExpression()->action(InterpretatorArgs(functions, variablesGlobal, variables, stack));
}

void Interpretator::executeChild(Node* tree) {
    for (auto node : tree->getChildren()) {
        executeChild(node);
    }
    /*if (stack.empty() && tree->getExpression()->getType() == "var") {
        stack.
    }*/
    tree->getExpression()->action(InterpretatorArgs(functions, variablesGlobal, variables, stack));
}

void Interpretator::cleanStack() {
    while (!stack.empty()) {
        auto var = stack.top();
        stack.pop();
        delete var;
    }
}

const std::map<std::string, Var*>* Interpretator::getVariables() const {
    return variables;
}

std::stack<Var*>& Interpretator::getStack() {
    return stack;
}