#pragma once


#include <list>
#include <map>
#include <stack>
#include "Node.h"
#include "Var.h"


class Interpretator final {
private:
    std::list<std::map<std::string, Node*>*> functions;

    std::list<std::map<std::string, Var*>*> variablesGlobal;
    std::map<std::string, Var*>* variables;

    std::stack<Var*> stack;

    void cleanStack();

public:
    explicit Interpretator(std::map<std::string, Node*>* functions);
    explicit Interpretator(
        const std::list<std::map<std::string, Node*>*>& functions,
        const std::list<std::map<std::string, Var*>*>& variablesGlobal
    );

    ~Interpretator();

    void execute(Node*);
    void executeChild(Node*);

    const std::map<std::string, Var*>* getVariables() const;
    std::stack<Var*>& getStack();
};