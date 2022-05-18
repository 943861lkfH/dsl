#pragma once
#include "Expression.h"
#include "Node.h"
#include <list>

#ifndef EXPWHILE_H
#define EXPWHILE_H
class ExpWhile final : public Expression
{
public:
	ExpWhile(Node* whileBrascet, Node* body, int line, std::map<std::string, Node*>* functions);
	~ExpWhile();
private:
	std::map<std::string, Node*>* functions;
	Node* whileBrascet;
	Node*  body;
	virtual void action(const InterpretatorArgs& args);
	virtual std::string toString() const;
};
#endif
