#pragma once
#include "Expression.h"

#ifndef EXPOP_H
#define EXPOP_H
class ExpOp final : public Expression
{
public:
	ExpOp(std::string name, int line);
	std::string getName();
private:
	std::string name;
	virtual void action(const InterpretatorArgs& args);
	virtual std::string toString() const;
};
#endif
