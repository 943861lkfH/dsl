#include "ExpIf.h"
#include "Interpretator.h"

ExpIf::ExpIf(Node* ifBrascet, Node* body, int line) :Expression("if", line) {
	this->ifBrascet = ifBrascet;
	this->body = body;
}

ExpIf::~ExpIf() {
    delete ifBrascet;
    delete body;
    /*for (const auto& func : *functions) {
        delete func.second;
    }
    delete functions;*/
}

void ExpIf::action(const InterpretatorArgs& args){
    args.variablesGlobal.push_front(args.variables);

    Interpretator compilerCondition(args.functions, args.variablesGlobal);
    compilerCondition.executeChild(ifBrascet);

    auto condition = compilerCondition.getStack().top();
    compilerCondition.getStack().pop();

    if ((bool)*condition) {
        //args.functions.push_front(functions);

        Interpretator compilerBlock(args.functions, args.variablesGlobal);
        compilerBlock.execute(body);

        args.functions.pop_front();
    }

    args.variablesGlobal.pop_front();
    delete condition;
}

std::string ExpIf::toString() const {
    return NULL; // "if\n        " + ifBrascet->toString(2) + "\n        execute " + body->toString(2);
}