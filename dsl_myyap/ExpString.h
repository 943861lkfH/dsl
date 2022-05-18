#pragma once
#include "Expression.h"

#ifndef EXPSTRING_H
#define EXPSTRING_H
class ExpString final : public Expression
{
public:
	ExpString(std::string name, int line);
private:
	std::string name;
	int line;
	virtual void action(const InterpretatorArgs& args);
	virtual std::string toString() const;
};
#endif
