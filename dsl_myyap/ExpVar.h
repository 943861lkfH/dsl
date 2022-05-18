#pragma once
#include "Expression.h"

#ifndef EXPVAR_H
#define EXPVAR_H
class ExpVar final : public Expression
{
public:
	ExpVar(std::string name, int line);
private:
	std::string name;
	int line;
	virtual void action(const InterpretatorArgs& args);
	virtual std::string toString() const;
	bool callVariableFrom(std::map<std::string, Var*>* container, std::stack<Var*>& stack);
};
#endif
