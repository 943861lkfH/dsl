#pragma once
#include "Expression.h"
#include "Node.h"
#include <list>

#ifndef EXPIF_H
#define EXPIF_H
class ExpIf final : public Expression
{
public:
	ExpIf(Node* whileBrascet, Node* body, int line);
	~ExpIf();
private:
	Node* ifBrascet;
	Node* body;
	virtual void action(const InterpretatorArgs& args);
	virtual std::string toString() const;
};
#endif
