#pragma once
#include "Expression.h"

#ifndef EXPDOUBLE_H
#define EXPDOUBLE_H
class ExpDouble final : public Expression
{
public:
	ExpDouble(std::string name, int line);
private:
	std::string name;
	int line;
	virtual void action(const InterpretatorArgs& args);
	virtual std::string toString() const;
};
#endif
