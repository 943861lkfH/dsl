#pragma once
#include "Expression.h"

#ifndef EXPBOOL_H
#define EXPBOOL_H
class ExpBool final: public Expression
{
public:
	ExpBool(std::string name, int line);
private:
	bool name;
	int line;
	virtual void action(const InterpretatorArgs& args);
	virtual std::string toString() const;
};
#endif

