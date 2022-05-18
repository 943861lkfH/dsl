#include "ExpVarAssign.h"

ExpVarAssign::ExpVarAssign(std::string name, int line) :Expression("varAssign", name, line) {
    this->name = name;
    this->line = line;
}

void ExpVarAssign::action(const InterpretatorArgs& args) {
    if (!args.stack.empty()) {
        auto val = args.stack.top();
        args.stack.pop();

        for (auto scope : args.variablesGlobal) {
            auto it = scope->find(name);
            if (it != scope->end()) {
                auto var = it->second;
                scope->insert_or_assign(name, val);
                delete var;
                return;
            }
        }

        auto it = args.variables->find(name);
        if (it != args.variables->end()) {
            auto var = it->second;
            args.variables->insert_or_assign(name, val);
            delete var;
        }
        else {
            args.variables->insert_or_assign(name, val);
        }
    }
}

std::string ExpVarAssign::toString() const {
    return name;
}