#include "Parser.h"
#include <stack>

Parser::Parser(std::list<Token*> tokenList, Node* tree) {
	this->tokenList = tokenList;
	this->tree = tree;
	prior["="] = 0;
	prior["+"] = 1;
	prior["-"] = 1;
	prior["*"] = 2;
	prior["/"] = 2;
	prior["^"] = 3;
	prior["("] = 4;
	prior[")"] = 5;
	addSyntaxLine(tokenList);
}

void Parser::addSyntaxLine(std::list<Token*> tokenList) {
	std::list<Token*> list;
	bool semicolon = false;
	int bracket = 0, brace = 0;
	for (auto token : tokenList) {
		std::string type = token->getType();
		if (type == "SEMICOLON_OP") {
			if ((brace == 0))
				semicolon = true;
			list.push_back(token);
		}
		else {
			if (type == "VAR" || type == "WHILE_KW" || type == "IF_KW" || type == "ELSE_KW" || type == "#function#"){
				if (!list.empty() && (semicolon == true || (brace == 0 && bracket == 0)))
				{
					checkSyntax(list);
					bracket = 0;
					brace = 0;
					list.clear();
					semicolon = false;
				}
			}
			else if (type == "L_BRACKET")
				bracket++;
			else if (type == "R_BRACKET")
				bracket--;
			else if (type == "L_BRACE")
				brace++;
			else if (type == "R_BRACE") {
				brace--;
				if (!list.empty() && (semicolon == true || (brace == 0 && bracket == 0)))
				{
					list.push_back(token);
					checkSyntax(list);
					bracket = 0;
					brace = 0;
					list.clear();
					semicolon = false;
				}
			}
			list.push_back(token);
		}
	}
	if (!list.empty())
	{
		checkSyntax(list);
		list.clear();
	}
}

void Parser::checkSyntax(std::list<Token*> list) {
	begin = list.begin();
	end = --list.end();
	std::string type = (*begin)->getType();
	if ((type == "VAR") && (checkVAR())) {
		for (auto i : list) {
			std::cout << i->getName() << "  ";
		}
		std::cout << '\n';
		parseVar(list);
	}
	/*else if ((type == "FUNC_NAME") && (checkFUNC()))
		funcToExpr(list);*/
	else if (checkKW()) {
		if (type == "IF_KW")
			ifToExpr(list);
		if (type == "WHILE_KW")
			whileToExpr(list);
	}
	//std::cout << "WARNING: SYNTAX ERROR IN LINES " << (*list.begin())->getLine() << "-" << (*list.end())->getLine();
}

bool Parser::checkVAR() {
	if((*begin)->getType() == "VAR")
		if ((*++begin)->getType() == "EQUALS_OP")
		{
			++begin;
			if (checkEXPR())
				return true;
		}
	return false;
}

bool Parser::checkEXPR() { 
	if (std::regex_match((*begin)->getName(), std::regex(R"([\+\-])")))
		++begin;
	while (begin != end) {
		if(checkVALUE())
			++begin;
		if (std::regex_match((*begin)->getName(), std::regex(R"(([\+\-\/\*\^\<\>])|(\|\|)|(&&)|(>=)|(<=)|(<>)|(==))")))
		{
			++begin;
			if (checkVALUE())
				++begin;
			else return false;
		}
		std::string type = (*begin)->getType();
		if ((type == "R_BRACKET")||(type == "R_BRACE")||(type == "SEMICOLON_OP"))
			return true;
	}
	return false;
}

bool Parser::checkVALUE() {
	std::string type = (*begin)->getType();
	if (type == "VAR" || type == "DIGIT" || type == "STRING") {
		return true;
	}
	else if (checkBRACKET())
		return true;
	return false;
}

bool Parser::checkBRACKET() {
	if ((*begin)->getType() == "L_BRACKET") {
		++begin;
		checkEXPR();
	}
	if ((*begin)->getType() == "R_BRACKET")
		return true;
	return false;
}

bool Parser::checkBRACE() {
	if ((*begin)->getType() == "L_BRACE") {
		++begin;
		while (begin != end)
		{
			if ((*begin)->getType() == "SEMICOLON_OP")
				++begin;
			std::string type = (*begin)->getType();
			if (type == "R_BRACE")
				return true;
			if (type == "#function#")
				if (!checkFUNC())
					return false;
			if (type == "IF_KW" || type == "ELSE_KW" || type == "WHILE_KW") {
				if (!checkKW())
					return false;
			}
			else if (!checkVAR())
				return false;
		}
	}	
	return false;
}

bool Parser::checkKW() {
	std::string type = (*begin)->getType();
	if (type == "IF_KW" || type == "WHILE_KW") {
		++begin;
		if (checkBRACKET())
		{
			++begin;
			if (checkBRACE())
				return true;
		}
	}
	return false;
}

bool Parser::checkFUNC() {
	++begin;
	if ((*begin)->getType() == "VAR")
	{
		if (((*begin)->getType() == "L_BRASCET") && ((*++begin)->getType() == "R_BRASCET")) {
			++begin;
			if (checkBRACE())
				return true;
		}
	}
	return false;
}

void Parser::parseVar(std::list<Token*> list) {
	tree->addChildBack(addNode(polish(varToExpr(list))));
}

std::list<Expression*> Parser::varToExpr(std::list<Token*> list) {
	std::list <Expression*> listExp;
	bool op = false;
	if (((*list.begin())->getType() == "VAR") && (((*(++list.begin()))->getType() == "EQUALS_OP")))
	{
		listExp.push_back(new ExpVarAssign((*list.begin())->getName(), (*list.begin())->getLine()));
		list.pop_front();
	}
	for (auto token : list)
	{
		std::string type = token->getType();
		std::string name = token->getName();
		int line = token->getLine();
		if (op) {
			if (std::regex_match(name, std::regex(R"([\+\-])")))
			{
				listExp.push_back(new ExpInt("0", line));
				listExp.push_back(new ExpOp(name, line));
				continue;
			}
			op = false;
		}
		if (name == "=" || name == "(") {
			listExp.push_back(new ExpOp(name, line));
			op = true;
			continue;
		}
		if (type == "VAR")
			listExp.push_back(new ExpVar(name, line));
		else if (type == "DIGIT") {
			if (std::regex_match(name, std::regex(R"(0|([1-9][0-9]*))")))
				listExp.push_back(new ExpInt(name, line));
			else if (std::regex_match(name, std::regex(R"([1-9][0-9]*\.[0-9]*)")))
				listExp.push_back(new ExpDouble(name, line));
		}
		else if (type == "STRING")
			listExp.push_back(new ExpString(name, line));
		else if (type == "BOOL")
			listExp.push_back(new ExpBool(name, line));
		else if (type == "SEMICOLON_OP")
			continue;
		else listExp.push_back(new ExpOp(name, line));
	}
	return listExp;
}

std::list<Expression*> Parser::polish(std::list<Expression*> list) {
	std::stack <Expression*> ops;
	std::list <Expression*> polish;
	for (auto exp : list) {
		if (exp->getType() == "op")
		{
			if (!ops.empty()) {
				Expression* backOpExp = ops.top();
				std::string backOp = backOpExp->getName();
				std::string newOp = exp->getName();
				if (priority(backOp, newOp) && backOp != "(") {
					ops.pop();
					ops.push(exp);
					polish.push_back(backOpExp);
					continue;
				}
			}
			if (exp->getName() == ")")
			{
				Expression* current = ops.top();
				while (current->getName() != "(") {
					polish.push_back(current);
					ops.pop();
					current = ops.top();
				}
				ops.pop();
				continue;
			}
			ops.push(exp);
		}
		else polish.push_back(exp);
	}
	while (!ops.empty()) {
		polish.push_back(ops.top());
		ops.pop();
	}
	/*if (polish.back()->getName() == "=")
		polish.pop_back();*/
	return polish;
}

bool Parser::priority(std::string backOp, std::string newOp) {
	if (prior[backOp] >= prior[newOp])
		return true;
	return false;
}

void Parser::ifToExpr(std::list<Token*> list) {
	int line = list.front()->getLine();
	list.pop_front();
	list.pop_front();
	std::list<Token*> listIf;
	while (!(list.front()->getName() == ")")) {
		listIf.push_back(list.front());
		list.pop_front();
	}
	list.pop_front();
	Node* expIfBrascet = addNode(polish(varToExpr(listIf)));
	listIf.clear();
	list.pop_front();

	int line1 = list.front()->getLine();
	int line2 = list.front()->getLine();
	Node* rootBody = new Node(new ExpBody("if", line1));
	while (!list.empty()) {
		if (line2 != line1) {
			rootBody->addChildBack(addNode(polish(varToExpr(listIf))));
			listIf.clear();
			line1 = line2;
		}
		if (list.front()->getName() == "}") {
			list.pop_front();
			continue;
		}
		listIf.push_back(list.front());
		list.pop_front();
		if (list.front()->getName() == "}")
			line2 = line1 + 1;
		else line2 = list.front()->getLine();
	}
	/*expIfBrascet->addChildBack(rootBody);
	tree->addChildBack(expIfBrascet);*/
	tree->addChildBack(new Node(new ExpIf(expIfBrascet, rootBody, line)));
}

void Parser::whileToExpr(std::list<Token*> list) {
	int line = list.front()->getLine();
	list.pop_front();
	list.pop_front();
	std::list<Token*> listWhile;
	while (!(list.front()->getName() == ")")) {
		listWhile.push_back(list.front());
		list.pop_front();
	}
	list.pop_front();
	Node* expWhileBrascet = addNode(polish(varToExpr(listWhile)));
	listWhile.clear();
	list.pop_front();

	int line1 = list.front()->getLine();
	int line2 = list.front()->getLine();
	Node* rootBody = new Node(new ExpBody("while", line1));
	while (!list.empty()) {
		if (line2 != line1) {
			rootBody->addChildBack(addNode(polish(varToExpr(listWhile))));
			listWhile.clear();
			line1 = line2;
		}
		if (list.front()->getName() == "}") {
			list.pop_front();
			continue;
		}
		listWhile.push_back(list.front());
		list.pop_front();
		if (list.front()->getName() == "}")
			line2 = line1 + 1;
		else line2 = list.front()->getLine();
	}
	auto functionsLocal = new std::map<std::string, Node*>();
	/*expWhileBrascet->addChildBack(rootBody);
	tree->addChildBack(expWhileBrascet);*/
	tree->addChildBack(new Node(new ExpWhile(expWhileBrascet, rootBody, line, functionsLocal)));
}

//void Parser::funcToExpr(std::list<Token*> list) {
//	
//}

Node* Parser::addNode(std::list<Expression*> list) {
	std::stack<Node*> stackNode;
	bool equals = false;
	for (auto exp : list) {
		if (exp->getName() == "=") {
			equals = true;
		}
		else {
			Node* node = new Node(exp);
			if (exp->getType() == "op") {
				node->addChildFront(stackNode.top());
				stackNode.pop();
				node->addChildFront(stackNode.top());
				stackNode.pop();
			}
			stackNode.push(node);
		}
	}
	if (equals) {
		Node* value = stackNode.top();
		stackNode.pop();
		Node* var = stackNode.top();
		stackNode.pop();
		var->addChildFront(value);
		return var;
	}
	Node* node = stackNode.top();
	return node;
}
