#pragma once
#include "Expression.h"

#ifndef EXPINT_H
#define EXPINT_H
class ExpInt final : public Expression
{
public:
	ExpInt(std::string name, int line);
private:
	std::string name;
	int line;
	virtual void action(const InterpretatorArgs& args);
	virtual std::string toString() const;
};
#endif
