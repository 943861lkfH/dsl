#include "ExpWhile.h"
#include "Interpretator.h"

ExpWhile::ExpWhile(Node* whileBrascet, Node* body, int line, std::map<std::string, Node*>* functions) :Expression("while", line) {
	this->whileBrascet = whileBrascet;
	this->body = body;
    this->functions = functions;
}

ExpWhile::~ExpWhile() {
    delete whileBrascet;
    delete body;
    /*for (const auto& func : *functions) {
        delete func.second;
    }
    delete functions;*/
}

void ExpWhile::action(const InterpretatorArgs& args){
    args.variablesGlobal.push_front(args.variables);

    Interpretator compilerCondition(args.functions, args.variablesGlobal);
    compilerCondition.executeChild(whileBrascet);

    auto condition = compilerCondition.getStack().top();
    compilerCondition.getStack().pop();

    while ((bool)*condition) {
        args.functions.push_front(functions);

        Interpretator compilerExecute(args.functions, args.variablesGlobal);
        compilerExecute.execute(body);

        args.functions.pop_front();

        compilerCondition.executeChild(whileBrascet);
        delete condition;
        condition = compilerCondition.getStack().top();
        compilerCondition.getStack().pop();
    }

    args.variablesGlobal.pop_front();
    delete condition;
}

std::string ExpWhile::toString() const {
    return NULL;// "while\n        " + whileBrascet->toString(2) + "\n        execute " + body->toString(2);
}