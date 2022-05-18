#include <stdio.h>
#include "Lexer.h"
#include "Token.h"
#include "Parser.h"
#include "ExpVar.h"
#include "Interpretator.h"
#include "Var.h"

#include <fstream>
#include <iostream>

int main() {

    Lexer* lexer = new Lexer("\Code.txt");
    lexer->lexemAnalys();

    Node* nodeboss = new Node(new ExpVar("root", 0));
    Parser* parser = new Parser(lexer->tokenList, nodeboss);
    //nodeboss->printTree(0);

    auto functions = new std::map<std::string, Node*>;
    Interpretator compiler(functions);
    compiler.execute(nodeboss);

    std::cout << std::endl;
    for (const auto& var : *compiler.getVariables()) {
        std::cout << std::endl << var.first << " = " << (std::string)*var.second;
    }
    std::cout << std::endl;

	return 0;
}