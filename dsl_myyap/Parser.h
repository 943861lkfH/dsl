#pragma once

#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <regex>
#include <string>
#include <stack>
#include "Token.h"
#include "ExpBody.h"
#include "ExpBool.h"
#include "ExpInt.h"
#include "ExpDouble.h"
#include "ExpString.h"
#include "ExpVarAssign.h"
#include "ExpVar.h"
#include "ExpIf.h"
#include "ExpWhile.h"
#include "ExpWhile.h"
#include "ExpOp.h"
#include "ExpFunc.h"
#include "Expression.h"
#include "Node.h"
#include <map>


class Parser
{
public:
	std::list<Token*> tokenList;
	Parser(std::list<Token*> tokenList, Node* tree);
	~Parser() = default;
	void addSyntaxLine(std::list<Token*> tokenList);
	std::map <std::string, int> prior;

private:
	void checkSyntax(std::list<Token*> list);
	bool checkVAR();
	bool checkEXPR();
	bool checkVALUE();
	bool checkBRACKET();
	bool checkBRACE();
	bool checkFUNC();
	bool checkKW();
	bool priority(std::string backOp, std::string newOp);
	void parseVar(std::list<Token*> list);
	Node* addNode(std::list<Expression*> list);
	std::list<Expression*> varToExpr(std::list<Token*> list);
	void ifToExpr(std::list<Token*> list);
	void whileToExpr(std::list<Token*> list);
	//void funcToExpr(std::list<Token*> list);
	std::list<Expression*> polish(std::list<Expression*> list);
	std::list<Token*>::iterator begin;
	std::list<Token*>::iterator end;
	Node* tree;

};
#endif

