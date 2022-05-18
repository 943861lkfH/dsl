#pragma once
#include "Expression.h"

#ifndef EXPVARASSIGN_H
#define EXPVARASSIGN_H
class ExpVarAssign final : public Expression
{
public:
	ExpVarAssign(std::string name, int line);
private:
	std::string name;
	int line;
	virtual void action(const InterpretatorArgs& args);
	virtual std::string toString() const;
};
#endif
