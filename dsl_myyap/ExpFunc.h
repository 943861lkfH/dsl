#pragma once
#include "Expression.h"
#include "Node.h"

#ifndef EXPFUNC_H
#define EXPFUNC_H
class ExpFunc final : public Expression
{
public:
	ExpFunc(std::string name, std::list<Node*> arguments, int line);
private:
	std::string name;
	std::list<Node*> arguments;
	virtual void action(const InterpretatorArgs& args) {};
	virtual std::string toString() const override { return ""; };
};
#endif

